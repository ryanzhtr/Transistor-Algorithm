import os
import random
import cv2
import numpy as np
from tqdm import tqdm

class ImageAugmentor:
    def __init__(self, train_dir):
        self.train_dir = train_dir
        self.classes = ['1', '2', '3', '4', '5', 'base', 'sb']
        
    def rotate_image(self, image, angle):
        """旋转图像"""
        center = (image.shape[1] // 2, image.shape[0] // 2)
        matrix = cv2.getRotationMatrix2D(center, angle, 1.0)
        rotated = cv2.warpAffine(image, matrix, (image.shape[1], image.shape[0]))
        return rotated
    
    def adjust_brightness(self, image, factor):
        """调整亮度"""
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        hsv = hsv.astype(np.float32)
        hsv[:,:,2] = hsv[:,:,2] * factor
        hsv[:,:,2] = np.clip(hsv[:,:,2], 0, 255)
        hsv = hsv.astype(np.uint8)
        return cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
    
    def add_gaussian_noise(self, image, mean=0, sigma=25):
        """添加高斯噪声"""
        noise = np.random.normal(mean, sigma, image.shape)
        noisy_image = image + noise
        return np.clip(noisy_image, 0, 255).astype(np.uint8)
    
    def gaussian_blur(self, image, kernel_size=3):
        """高斯模糊"""
        return cv2.GaussianBlur(image, (kernel_size, kernel_size), 0)
    
    def random_crop(self, image, crop_percent=0.9):
        """随机裁剪后resize回原始大小"""
        height, width = image.shape[:2]
        crop_height = int(height * crop_percent)
        crop_width = int(width * crop_percent)
        
        y = random.randint(0, height - crop_height)
        x = random.randint(0, width - crop_width)
        
        cropped = image[y:y+crop_height, x:x+crop_width]
        return cv2.resize(cropped, (width, height))
    
    def apply_augmentation(self, image):
        """应用随机增强"""
        augmented = image.copy()
        
        # 随机选择1-3种增强方法组合
        num_augmentations = random.randint(1, 3)
        augmentation_methods = random.sample([
            lambda img: self.rotate_image(img, random.uniform(-15, 15)),
            lambda img: self.adjust_brightness(img, random.uniform(0.7, 1.3)),
            lambda img: self.add_gaussian_noise(img),
            lambda img: self.gaussian_blur(img),
            lambda img: self.random_crop(img)
        ], num_augmentations)
        
        for method in augmentation_methods:
            augmented = method(augmented)
            
        return augmented
    
    def augment_dataset(self, samples_per_class=200):
        """对每个类别进行图像增强"""
        for class_name in self.classes:
            class_dir = os.path.join(self.train_dir, class_name)
            
            # 获取所有图片文件
            image_files = [f for f in os.listdir(class_dir) if f.endswith('.png')]
            
            # 找到最大编号
            max_number = max([int(f.split('.')[0]) for f in image_files])
            next_number = max_number + 1
            
            # 随机选择图片进行增强
            selected_files = random.sample(image_files, min(samples_per_class, len(image_files)))
            
            print(f"正在处理类别 {class_name}")
            for file_name in tqdm(selected_files):
                # 读取原始图片
                image_path = os.path.join(class_dir, file_name)
                original = cv2.imread(image_path)
                
                if original is None:
                    print(f"无法读取图片: {image_path}")
                    continue
                
                # 应用增强
                augmented = self.apply_augmentation(original)
                
                # 保存增强后的图片
                new_file_name = f"{next_number:04d}.png"
                output_path = os.path.join(class_dir, new_file_name)
                cv2.imwrite(output_path, augmented)
                
                next_number += 1

def main():
    # 设置训练数据目录
    train_dir = "dataset/train"  # 请修改为你的实际路径
    
    # 创建增强器并处理数据集
    augmentor = ImageAugmentor(train_dir)
    augmentor.augment_dataset(200)

if __name__ == "__main__":
    main()