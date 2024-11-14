#include "AutoShootNode.h"

AutoShootNode::AutoShootNode() 
    : Node("auto_shoot_node"), camera("192.168.10.10", "192.168.10.25") {
    // 初始化 ROS 相关设置
    pub_ = this->create_publisher<rm_interface::msg::Position>("Position_raw", 50);
    sub_ = this->create_subscription<rm_interface::msg::MarkAngle>(
        "timemark", 50, std::bind(&AutoShootNode::mark_callback, this, std::placeholders::_1));

    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(2), std::bind(&AutoShootNode::timer_callback, this));

    // 初始化其他组件
    detectArmor = std::make_shared<DetectArmor>();
    trackArmor = std::make_shared<TrackArmor>();

    // 启动相机线程
    camera_thread_ = std::thread(&AutoShootNode::workflow, this);
}

AutoShootNode::~AutoShootNode() {
    if (camera_thread_.joinable()) {
        camera_thread_.join();
    }
}

// 回调函数：MarkAngle消息
void AutoShootNode::mark_callback(const rm_interface::msg::MarkAngle::SharedPtr msg) {
    mark_ = msg->mark;
    angle_world_ = msg->angle;
    enemy_color_ = msg->tnndcolor.data;
}

// 定时回调函数：发布装甲板位置数据
void AutoShootNode::timer_callback() {
    auto msg = rm_interface::msg::Position();
    msg.depth = depth_;
    msg.height = height_;
    msg.bias = bias_;
    msg.mark = mark_;

    if (update_flag_ != mark_) {
        update_flag_ = mark_;
        pub_->publish(msg);
    }
}

// 相机捕获与装甲板检测和追踪的工作流
void AutoShootNode::workflow() {
    while (rclcpp::ok()) {
        try {
            std::lock_guard<std::mutex> lock(camera_mutex_);

            // 获取相机图像
            image_copy_ = camera.get_image();
            if (image_copy_.empty()) {
                RCLCPP_WARN(this->get_logger(), "Failed to capture image");
                continue;
            }

            // 进行装甲板检测
            detect_board(image_copy_);

            // 进行装甲板追踪
            track_armor();

        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Error in workflow: %s", e.what());
        }
    }
}

// 装甲板检测
void AutoShootNode::detect_board(const cv::Mat &src) {
    detectArmor->set_enemy_color(enemy_color_);
    detectArmor->exe(src);
    boards_detected_ = detectArmor->get_armor();

    // 这里可以根据需求更新其他信息
    height_ = detectArmor->get_height();
    depth_ = detectArmor->get_depth();
    bias_ = detectArmor->get_bias();
}

// 装甲板追踪
void AutoShootNode::track_armor() {
    double dt = (time_ - last_time_) / 1e9;  // 时间差，单位秒
    trackArmor->set_dt(dt);
    trackArmor->main(boards_detected_, detectArmor->get_T(), detectArmor->get_R(), angle_world_);

    height_ = trackArmor->get_height();
    depth_ = trackArmor->get_depth();
    bias_ = trackArmor->get_bias();

    last_time_ = time_;
}

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AutoShootNode>());
    rclcpp::shutdown();
    return 0;
}
