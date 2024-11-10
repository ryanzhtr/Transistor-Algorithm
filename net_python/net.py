import os
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, random_split
from torchvision import datasets, transforms, models
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import confusion_matrix, classification_report

class RobotImageClassifier(nn.Module):
    def __init__(self, num_classes=7):
        super(RobotImageClassifier, self).__init__()
        
        # 自定义轻量级CNN
        self.features = nn.Sequential(
            # 第一层卷积块
            nn.Conv2d(3, 32, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(32),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=2, stride=2),
            nn.Dropout(0.25),
            
            # 第二层卷积块
            nn.Conv2d(32, 64, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(64),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=2, stride=2),
            nn.Dropout(0.25),
            
            # 第三层卷积块
            nn.Conv2d(64, 128, kernel_size=3, stride=1, padding=1),
            nn.BatchNorm2d(128),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=2, stride=2),
            nn.Dropout(0.25)
        )
        
        # 计算全连接层输入维度
        with torch.no_grad():
            x = torch.randn(1, 3, 48, 64)
            x = self.features(x)
            num_features = x.view(1, -1).size(1)
        
        # 全连接层
        self.classifier = nn.Sequential(
            nn.Linear(num_features, 256),
            nn.ReLU(inplace=True),
            nn.BatchNorm1d(256),
            nn.Dropout(0.5),
            nn.Linear(256, num_classes)
        )
    
    def forward(self, x):
        x = self.features(x)
        x = x.view(x.size(0), -1)  # 展平
        x = self.classifier(x)
        return x

class RobotDataLoader:
    def __init__(self, base_path):
        self.base_path = base_path
        self.train_dir = os.path.join(base_path, 'train')
        self.test_dir = os.path.join(base_path, 'test')
        
        # 数据增强
        self.train_transform = transforms.Compose([
            transforms.Resize((48, 64)),
            transforms.RandomHorizontalFlip(),
            transforms.RandomRotation(10),
            transforms.ColorJitter(brightness=0.2, contrast=0.2),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406], 
                               std=[0.229, 0.224, 0.225])
        ])
        
        self.test_transform = transforms.Compose([
            transforms.Resize((48, 64)),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406], 
                               std=[0.229, 0.224, 0.225])
        ])
    
    def get_data_loaders(self, batch_size=32, val_split=0.1):
        try:
            # 训练集
            train_dataset = datasets.ImageFolder(
                self.train_dir, 
                transform=self.train_transform
            )
            
            # 划分训练集和验证集
            val_size = int(len(train_dataset) * val_split)
            train_size = len(train_dataset) - val_size
            train_dataset, val_dataset = random_split(
                train_dataset, 
                [train_size, val_size]
            )
            
            train_loader = DataLoader(
                train_dataset, 
                batch_size=batch_size, 
                shuffle=True, 
                num_workers=4,
                pin_memory=True
            )
            
            val_loader = DataLoader(
                val_dataset,
                batch_size=batch_size,
                shuffle=False,
                num_workers=4,
                pin_memory=True
            )
            
            # 测试集
            test_dataset = datasets.ImageFolder(
                self.test_dir, 
                transform=self.test_transform
            )
            test_loader = DataLoader(
                test_dataset, 
                batch_size=batch_size, 
                shuffle=False, 
                num_workers=4,
                pin_memory=True
            )
            
            return train_loader, val_loader, test_loader, train_dataset.dataset.classes
            
        except Exception as e:
            print(f"数据加载错误: {str(e)}")
            raise

class Trainer:
    def __init__(self, model, train_loader, val_loader, test_loader, classes):
        self.model = model
        self.train_loader = train_loader
        self.val_loader = val_loader
        self.test_loader = test_loader
        self.classes = classes
        
        # 设备
        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.model.to(self.device)
        
        # 损失函数和优化器
        self.criterion = nn.CrossEntropyLoss()
        self.optimizer = optim.Adam(
            self.model.parameters(), 
            lr=0.001, 
            weight_decay=1e-4
        )
        
        # 学习率调度器
        self.scheduler = optim.lr_scheduler.ReduceLROnPlateau(
            self.optimizer, 
            mode='min', 
            patience=5, 
            factor=0.5
        )
        
        # 最佳模型保存
        self.best_val_acc = 0
        self.best_model_path = 'best_model.pth'
    
    def save_model(self, path):
        torch.save({
            'model_state_dict': self.model.state_dict(),
            'optimizer_state_dict': self.optimizer.state_dict(),
            'scheduler_state_dict': self.scheduler.state_dict(),
        }, path)
    
    def load_model(self, path):
        checkpoint = torch.load(path)
        self.model.load_state_dict(checkpoint['model_state_dict'])
        self.optimizer.load_state_dict(checkpoint['optimizer_state_dict'])
        self.scheduler.load_state_dict(checkpoint['scheduler_state_dict'])
    
    def train(self, epochs=50):
        history = {
            'train_loss': [], 'train_acc': [],
            'val_loss': [], 'val_acc': []
        }
        
        for epoch in range(epochs):
            try:
                # 训练阶段
                self.model.train()
                train_loss = 0.0
                train_correct = 0
                train_total = 0
                
                for inputs, labels in self.train_loader:
                    inputs, labels = inputs.to(self.device), labels.to(self.device)
                    
                    self.optimizer.zero_grad()
                    outputs = self.model(inputs)
                    loss = self.criterion(outputs, labels)
                    loss.backward()
                    self.optimizer.step()
                    
                    train_loss += loss.item()
                    _, predicted = torch.max(outputs.data, 1)
                    train_total += labels.size(0)
                    train_correct += (predicted == labels).sum().item()
                
                # 验证阶段
                self.model.eval()
                val_loss = 0.0
                val_correct = 0
                val_total = 0
                
                with torch.no_grad():
                    for inputs, labels in self.val_loader:
                        inputs, labels = inputs.to(self.device), labels.to(self.device)
                        outputs = self.model(inputs)
                        loss = self.criterion(outputs, labels)
                        
                        val_loss += loss.item()
                        _, predicted = torch.max(outputs.data, 1)
                        val_total += labels.size(0)
                        val_correct += (predicted == labels).sum().item()
                
                # 计算指标
                train_loss /= len(self.train_loader)
                train_acc = 100 * train_correct / train_total
                val_loss /= len(self.val_loader)
                val_acc = 100 * val_correct / val_total
                
                # 记录历史
                history['train_loss'].append(train_loss)
                history['train_acc'].append(train_acc)
                history['val_loss'].append(val_loss)
                history['val_acc'].append(val_acc)
                
                # 学习率调度
                self.scheduler.step(val_loss)
                
                # 保存最佳模型
                if val_acc > self.best_val_acc:
                    self.best_val_acc = val_acc
                    self.save_model(self.best_model_path)
                
                # 打印信息
                print(f'Epoch {epoch+1}/{epochs}')
                print(f'Train Loss: {train_loss:.4f}, Train Acc: {train_acc:.2f}%')
                print(f'Val Loss: {val_loss:.4f}, Val Acc: {val_acc:.2f}%')
                
                # 清理GPU缓存
                if torch.cuda.is_available():
                    torch.cuda.empty_cache()
                    
            except Exception as e:
                print(f"训练错误: {str(e)}")
                raise
            
        return history
    
    def evaluate(self):
        try:
            self.model.eval()
            all_preds = []
            all_labels = []
            
            with torch.no_grad():
                for inputs, labels in self.test_loader:
                    inputs, labels = inputs.to(self.device), labels.to(self.device)
                    outputs = self.model(inputs)
                    _, preds = torch.max(outputs, 1)
                    
                    all_preds.extend(preds.cpu().numpy())
                    all_labels.extend(labels.cpu().numpy())
            
            # 详细指标
            print("\n分类报告:")
            print(classification_report(
                all_labels, 
                all_preds, 
                target_names=self.classes
            ))
            
            return all_preds, all_labels
            
        except Exception as e:
            print(f"评估错误: {str(e)}")
            raise

class ResultVisualizer:
    @staticmethod
    def plot_training_history(history):
        plt.figure(figsize=(12, 4))
        
        plt.subplot(1, 2, 1)
        plt.plot(history['train_acc'], label='训练准确率')
        plt.plot(history['val_acc'], label='验证准确率')
        plt.title('模型准确率')
        plt.xlabel('轮次')
        plt.ylabel('准确率')
        plt.legend()
        
        plt.subplot(1, 2, 2)
        plt.plot(history['train_loss'], label='训练损失')
        plt.plot(history['val_loss'], label='验证损失')
        plt.title('模型损失')
        plt.xlabel('轮次')
        plt.ylabel('损失')
        plt.legend()
        
        plt.tight_layout()
        plt.show()
    
    @staticmethod
    def plot_confusion_matrix(all_labels, all_preds, classes):
        cm = confusion_matrix(all_labels, all_preds)
        
        plt.figure(figsize=(10, 8))
        sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                    xticklabels=classes, 
                    yticklabels=classes)
        plt.title('混淆矩阵')
        plt.xlabel('预测标签')
        plt.ylabel('真实标签')
        plt.show()

def main():
    try:
        # 数据路径
        base_path = '/home/loule/RM/net/dataset'
        
        # 数据加载
        data_loader = RobotDataLoader(base_path)
        train_loader, val_loader, test_loader, classes = data_loader.get_data_loaders()
        
        # 模型初始化
        model = RobotImageClassifier(num_classes=len(classes))
        
        # 训练
        trainer = Trainer(model, train_loader, val_loader, test_loader, classes)
        history = trainer.train(epochs=5)
        
        # 加载最佳模型
        trainer.load_model(trainer.best_model_path)
        
        # 评估
        all_preds, all_labels = trainer.evaluate()
        
        # 可视化
        ResultVisualizer.plot_training_history(history)
        ResultVisualizer.plot_confusion_matrix(all_labels, all_preds, classes)
        
    except Exception as e:
        print(f"程序运行错误: {str(e)}")

if __name__ == '__main__':
    main()