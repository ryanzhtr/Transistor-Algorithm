#include <opencv2/opencv.hpp>
#include "LightBarFinder.h"

using namespace br;
using namespace cv;

int main(int argc, char** argv) {
    // 初始化视频流或相机
    VideoCapture cap(0);  // 使用默认相机
    if (!cap.isOpened()) {
        std::cerr << "无法打开相机" << std::endl;
        return -1;
    }

    // 创建LightBarFinder对象
    LightBarFinder lightBarFinder;
    LightBarBlobs lightBarBlobs;

    // 设置敌方颜色 (假设可以设置红色或蓝色)
    lightBarFinder.setEnemyColor(RED);  // 设置敌方为红色
    // lightBarFinder.setEnemyColor(BLUE);  // 设置敌方为蓝色

    while (true) {
        Mat frame;
        cap >> frame;  // 获取每帧图像
        if (frame.empty()) {
            std::cerr << "获取帧失败" << std::endl;
            break;
        }

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
                for (int i = 0; i < 4; i++)
                    line(frame, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
            }
        } else {
            std::cout << "未检测到灯条" << std::endl;
        }

        // 显示结果
        imshow("灯条识别", frame);

        // 按下 'q' 键退出循环
        if (waitKey(10) == 'q') break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
