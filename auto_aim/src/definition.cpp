#include "definition.h"

// Light 类的构造函数实现
Light::Light(const cv::RotatedRect &box) : el(box) {
    cv::Point2f center = el.center;
    float major = el.size.width;
    float minor = el.size.height;
    double angle = el.angle / 180.0 * M_PI - M_PI / 2;

    cv::Point2f major_axis_endpoint1(center.x - 0.5 * major * cos(angle), 
                                      center.y - 0.5 * minor * sin(angle));
    cv::Point2f major_axis_endpoint2(center.x + 0.5 * major * cos(angle), 
                                      center.y + 0.5 * minor * sin(angle));

    std::vector<cv::Point2f> p = {major_axis_endpoint1, major_axis_endpoint2};
    std::sort(p.begin(), p.end(), [](const cv::Point2f &a, const cv::Point2f &b) { return a.y < b.y; });
    top = p[0];
    bottom = p[1];
    length = cv::norm(top - bottom);

    angle += M_PI / 2;
    cv::Point2f minor_axis_endpoint1(center.x - 0.5 * major * cos(angle), 
                                      center.y - 0.5 * minor * sin(angle));
    cv::Point2f minor_axis_endpoint2(center.x + 0.5 * major * cos(angle), 
                                      center.y + 0.5 * minor * sin(angle));

    p = {minor_axis_endpoint1, minor_axis_endpoint2};
    std::sort(p.begin(), p.end(), [](const cv::Point2f &a, const cv::Point2f &b) { return a.y < b.y; });
    width = cv::norm(p[0] - p[1]);

    if (top.y == bottom.y) {
        tilt_angle = 90;
    } else {
        tilt_angle = std::degrees(std::atan(std::abs(top.x - bottom.x) / std::abs(top.y - bottom.y)));
    }
}

// Armor 类的构造函数实现
Armor::Armor(const cv::RotatedRect &rect, const std::vector<cv::Point2f> &points, ArmorSize size, int id, const std::vector<int> &light_ids)
    : rect(rect), points(points), size(size), id(id), light_ids(light_ids), prob(0) {}

// LeNet 类的构造函数实现
LeNet::LeNet() {
    conv1 = register_module("conv1", torch::nn::Conv2d(1, 6, 5, /*padding=*/2));
    pool1 = register_module("pool1", torch::nn::MaxPool2d(2, 2));
    conv2 = register_module("conv2", torch::nn::Conv2d(6, 16, 5));
    pool2 = register_module("pool2", torch::nn::MaxPool2d(2, 2));
    fc1 = register_module("fc1", torch::nn::Linear(16 * 5 * 5, 120));
    fc2 = register_module("fc2", torch::nn::Linear(120, 84));
    fc3 = register_module("fc3", torch::nn::Linear(84, 10));
    dropout = register_module("dropout", torch::nn::Dropout(0.25));
}

// LeNet 类的 forward 函数实现
torch::Tensor LeNet::forward(torch::Tensor x) {
    x = pool1(torch::relu(conv1(x)));
    x = pool2(torch::relu(conv2(x)));
    x = x.view({-1, 16 * 5 * 5});
    x = torch::relu(fc1(x));
    x = dropout(x);
    x = torch::relu(fc2(x));
    x = fc3(x);
    return x;
}

// PnPsolver 类的静态变量初始化
cv::Mat PnPsolver::camera_matrix = (cv::Mat_<double>(3, 3) << 
    1310.422473, 0, 652.1782683,
    0, 1310.496146, 541.894165,
    0, 0, 1);

cv::Mat PnPsolver::dist_coeffs = (cv::Mat_<double>(1, 5) <<
    -0.0807085646490320, 0.160324172041083, -0.0505325187663191, 0, 0);
