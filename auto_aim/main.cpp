// #include <opencv2/opencv.hpp>
// #include "Camera.h"
// #include "LightBarDetector.h"
// #include <iostream>
// #include <string>
// #include <chrono>

// extern cv::Mat g_image;
// extern pthread_mutex_t g_mutex;
// extern bool g_bExit;

// int main(int argc, char* argv[]) {
//     // 初始化互斥锁
//     pthread_mutex_init(&g_mutex, NULL);
    
//     // 相机参数
//     std::string deviceIp = "192.168.1.100"; // 请根据实际相机IP修改
//     std::string netIp = "192.168.1.1";      // 请根据实际网络配置修改
    
//     try {
//         // 初始化相机
//         Camera camera(deviceIp, netIp);
//         std::cout << "Camera initialized successfully." << std::endl;
        
//         // 初始化灯条检测器
//         Params params;  // 使用默认参数
//         LightBarDetector detector(params);
        
//         // 主循环
//         while (!g_bExit) {
//             cv::Mat frame;
            
//             // 获取图像
//             pthread_mutex_lock(&g_mutex);
//             if (!g_image.empty()) {
//                 frame = g_image.clone();
//             }
//             pthread_mutex_unlock(&g_mutex);
            
//             if (!frame.empty()) {
//                 // 显示原始图像
//                 cv::imshow("Original", frame);
                
//                 // 检测灯条
//                 std::vector<cv::Mat> images{frame};  // 创建包含单帧的图像vector
//                 detector.detectLights(images);       // 传入图像vector
                
//                 // 处理检测到的灯条
//                 detector.processLights();
                
//                 // 在图像上绘制检测结果
//                 cv::Mat result = frame.clone();
//                 const auto& lights = detector.detectLights();  // 获取检测到的灯条
//                 for (const auto& light : lights) {
//                     // 绘制旋转矩形
//                     cv::Point2f vertices[4];
//                     light.el.points(vertices);
//                     for (int i = 0; i < 4; i++) {
//                         cv::line(result, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
//                     }
//                 }
                
//                 // 显示结果
//                 cv::imshow("Detection Result", result);
//             }
            
//             // 处理按键
//             char key = cv::waitKey(1);
//             if (key == 27) { // ESC键退出
//                 g_bExit = true;
//                 break;
//             }
//         }
//     }
//     catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return -1;
//     }
    
//     // 清理资源
//     pthread_mutex_destroy(&g_mutex);
//     cv::destroyAllWindows();
    
//     return 0;
// }
#include <opencv2/opencv.hpp>
#include "Camera.h"
#include "LightBarDetector.h"
#include <iostream>
#include <string>
#include <chrono>

extern cv::Mat g_image;
extern pthread_mutex_t g_mutex;
extern bool g_bExit;

int main(int argc, char* argv[]) {
    // 初始化互斥锁
    pthread_mutex_init(&g_mutex, NULL);
    
    // 相机参数
    std::string deviceIp = "192.168.10.10"; // 请根据实际相机IP修改
    std::string netIp = "192.168.10.25";      // 请根据实际网络配置修改
    
    try {
        // 初始化相机
        Camera camera(deviceIp, netIp);
        std::cout << "Camera initialized successfully." << std::endl;
        
        // 初始化灯条检测器
        Params params;  // 使用默认参数
        LightBarDetector detector(params);
        
        // 主循环
        while (!g_bExit) {
            cv::Mat frame;
            
            // 获取图像
            pthread_mutex_lock(&g_mutex);
            if (!g_image.empty()) {
                frame = g_image.clone();
            }
            pthread_mutex_unlock(&g_mutex);
            
            if (!frame.empty()) {
                // 显示原始图像
                cv::imshow("Original", frame);
                
                // 检测灯条
                std::vector<cv::Mat> images{frame};  // 创建包含单帧的图像vector
                detector.detectLights(images);       // 传入图像vector
                
                // 处理检测到的灯条
                detector.processLights();
                
                // 在图像上绘制检测结果
                cv::Mat result = frame.clone();
                const auto& lights = detector.getLights();  // 获取检测到的灯条

                for (const auto& light : lights) {
                    // 绘制旋转矩形
                    cv::Point2f vertices[4];
                    light.el.points(vertices);
                    for (int i = 0; i < 4; i++) {
                        cv::line(result, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
                    }
                }
                
                // 显示结果
                cv::imshow("Detection Result", result);
            }
            
            // 处理按键
            char key = cv::waitKey(1);
            if (key == 27) { // ESC键退出
                g_bExit = true;
                break;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    // 清理资源
    pthread_mutex_destroy(&g_mutex);
    cv::destroyAllWindows();
    
    return 0;
}
