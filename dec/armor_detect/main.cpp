#include <opencv2/opencv.hpp>
#include "LightBarFinder.h"
<<<<<<< HEAD
#include "Camera.h" // 假设Camera.h是相机类的头文件
=======
>>>>>>> a748d59 (detect)

using namespace br;
using namespace cv;

int main(int argc, char** argv) {
<<<<<<< HEAD
    // 初始化相机对象
    Camera cam("192.168.10.10", "192.168.10.25");  // 使用相机的IP地址和电脑的IP地址
=======
    // 初始化视频流或相机
    VideoCapture cap(0);  // 使用默认相机
    if (!cap.isOpened()) {
        std::cerr << "无法打开相机" << std::endl;
        return -1;
    }
>>>>>>> a748d59 (detect)

    // 创建LightBarFinder对象
    LightBarFinder lightBarFinder;
    LightBarBlobs lightBarBlobs;

    // 设置敌方颜色 (假设可以设置红色或蓝色)
    lightBarFinder.setEnemyColor(RED);  // 设置敌方为红色
    // lightBarFinder.setEnemyColor(BLUE);  // 设置敌方为蓝色

<<<<<<< HEAD
    // 设定窗口名称
    namedWindow("灯条识别", WINDOW_NORMAL); 

    while (true) {
        Mat frame;
        
        // 线程锁定，确保安全访问共享图像数据
        pthread_mutex_lock(&g_mutex);
        if (!g_image.empty()) {
            g_image.copyTo(frame);  // 将共享图像数据复制到 frame
        } else {
            pthread_mutex_unlock(&g_mutex);  // 解锁
            std::cerr << "未获取到有效的帧数据" << std::endl;
            break;
        }
        pthread_mutex_unlock(&g_mutex);  // 解锁
=======
    while (true) {
        Mat frame;
        cap >> frame;  // 获取每帧图像
        if (frame.empty()) {
            std::cerr << "获取帧失败" << std::endl;
            break;
        }
>>>>>>> a748d59 (detect)

        // 识别灯条
        Point2f roi_offset(0, 0);  // 默认偏移量，可根据需要调整
        bool found = lightBarFinder.findLightBarBlobs(frame, lightBarBlobs, roi_offset);

        // 结果处理
        if (found) {
            std::cout << "检测到灯条数量: " << lightBarBlobs.size() << std::endl;
            for (const auto& blob : lightBarBlobs) {
                // 画出灯条的矩形框
                Point2f vertices[4];
                blob.points(vertices);
<<<<<<< HEAD
                for (int i = 0; i < 4; i++) {
                    line(frame, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
                }
=======
                for (int i = 0; i < 4; i++)
                    line(frame, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
>>>>>>> a748d59 (detect)
            }
        } else {
            std::cout << "未检测到灯条" << std::endl;
        }

        // 显示结果
        imshow("灯条识别", frame);
<<<<<<< HEAD
        cv::waitKey(1);
=======
>>>>>>> a748d59 (detect)

        // 按下 'q' 键退出循环
        if (waitKey(10) == 'q') break;
    }

<<<<<<< HEAD
    // 释放资源并关闭窗口
=======
    cap.release();
>>>>>>> a748d59 (detect)
    destroyAllWindows();
    return 0;
}
