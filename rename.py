import os
import shutil

def rename_images(source_dir):
    # 获取目录中所有png文件
    images = [f for f in os.listdir(source_dir) if f.endswith('.png')]
    
    # 按照文件名字典排序（可选）
    images.sort()
    
    # 遍历文件并重命名
    for index, filename in enumerate(images, start=1):
        # 构造新的文件名，使用三位数编号
        new_filename = f"{index:04d}.png"
        
        # 构造完整路径
        old_path = os.path.join(source_dir, filename)
        new_path = os.path.join(source_dir, new_filename)
        
        # 重命名
        os.rename(old_path, new_path)
        
        print(f"Renamed: {filename} -> {new_filename}")

# 使用示例
source_directory = "/home/loule/RM/net/dataset/sb"
rename_images(source_directory)