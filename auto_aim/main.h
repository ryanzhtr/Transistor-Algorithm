#ifndef AUTO_SHOOT_NODE_H
#define AUTO_SHOOT_NODE_H

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int16.hpp>
#include <rm_interface/msg/position.hpp>
#include <rm_interface/msg/mark_angle.hpp>
#include "connectCamera.hpp"  // 相机类头文件
#include "armorDetector.hpp"  // 装甲板检测类头文件
#include "tracker.hpp"        // 装甲板追踪类头文件

#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <chrono>

class AutoShootNode : public rclcpp::Node {
public:
    AutoShootNode();
    ~AutoShootNode();

private:
    // 回调函数：MarkAngle消息
    void mark_callback(const rm_interface::msg::MarkAngle::SharedPtr msg);

    // 定时回调函数：发布装甲板位置数据
    void timer_callback();

    // 相机捕获与装甲板检测和追踪的工作流
    void workflow();

    // 装甲板检测
    void detect_board(const cv::Mat &src);

    // 装甲板追踪
    void track_armor();

private:
    // 相机类实例
    connectCamera::Camera camera;
    std::thread camera_thread_;

    // ROS 组件
    rclcpp::Publisher<rm_interface::msg::Position>::SharedPtr pub_;
    rclcpp::Subscription<rm_interface::msg::MarkAngle>::SharedPtr sub_;
    rclcpp::TimerBase::SharedPtr timer_;

    // 装甲板检测和追踪对象
    std::shared_ptr<DetectArmor> detectArmor;
    std::shared_ptr<TrackArmor> trackArmor;

    // 标记与角度
    int mark_;
    float angle_world_;
    int enemy_color_;

    // 检测到的装甲板信息
    std::vector<Armor> boards_detected_;
    cv::Mat image_copy_;

    // 跟踪结果
    float depth_;
    float height_;
    float bias_;
    double time_;
    double last_time_;

    int update_flag_;

    // 互斥锁
    std::mutex camera_mutex_;
};

#endif // AUTO_SHOOT_NODE_H
