import os
import shutil
import random

def split_dataset(source_dir, train_ratio=0.8):
    # 创建训练集和测试集根目录
    train_dir = os.path.join(source_dir, 'train')
    test_dir = os.path.join(source_dir, 'test')
    
    # 确保目录存在
    os.makedirs(train_dir, exist_ok=True)
    os.makedirs(test_dir, exist_ok=True)
    
    # 遍历原始数据集中的每个子文件夹
    for folder in ['1', '2', '3', '4', '5', 'base', 'sb']:
        # 创建对应的训练集和测试集子文件夹
        train_folder = os.path.join(train_dir, folder)
        test_folder = os.path.join(test_dir, folder)
        
        os.makedirs(train_folder, exist_ok=True)
        os.makedirs(test_folder, exist_ok=True)
        
        # 获取当前文件夹中的所有图片
        source_folder = os.path.join(source_dir, folder)
        images = [f for f in os.listdir(source_folder) if f.endswith('.png')]
        
        # 随机打乱图片顺序
        random.shuffle(images)
        
        # 划分测试集和训练集
        test_count = 100  # 每个类别100张作为测试集
        test_images = images[:test_count]
        train_images = images[test_count:]
        
        # 复制测试集图片
        for img in test_images:
            src_path = os.path.join(source_folder, img)
            dst_path = os.path.join(test_folder, img)
            shutil.copy(src_path, dst_path)
        
        # 复制训练集图片
        for img in train_images:
            src_path = os.path.join(source_folder, img)
            dst_path = os.path.join(train_folder, img)
            shutil.copy(src_path, dst_path)
        
        # 重命名训练集图片
        train_images = sorted(os.listdir(train_folder))
        for index, img in enumerate(train_images, start=1):
            old_path = os.path.join(train_folder, img)
            new_path = os.path.join(train_folder, f'{index:04d}.png')
            os.rename(old_path, new_path)
        
        # 重命名测试集图片
        test_images = sorted(os.listdir(test_folder))
        for index, img in enumerate(test_images, start=1):
            old_path = os.path.join(test_folder, img)
            new_path = os.path.join(test_folder, f'{index:04d}.png')
            os.rename(old_path, new_path)
        
        print(f"Processed folder {folder}:")
        print(f"  Train images: {len(train_images)}")
        print(f"  Test images: {len(test_images)}")

# 使用示例
source_directory = "/home/loule/RM/net/dataset"
split_dataset(source_directory)