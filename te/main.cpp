#include "Camera.h"
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 设置设备和网络IP地址
    std::string deviceIp = "192.168.10.10";  // 设备的IP
    std::string netIp = "192.168.10.25";      // 网络IP

    // 创建 Camera 对象并初始化
    Camera camera(deviceIp, netIp);

    // 获取并显示图像
    while (!g_bExit) {
        // 使用互斥锁访问共享的全局图像
        pthread_mutex_lock(&g_mutex);
        if (!g_image.empty()) {
            cv::imshow("Grabbing Image", g_image);  // 显示抓取的图像
        }
        pthread_mutex_unlock(&g_mutex);

        // 按下任意键退出
        if (cv::waitKey(1) >= 0) {
            g_bExit = true;
        }
    }

    std::cout << "Exiting..." << std::endl;
    return 0;
}
