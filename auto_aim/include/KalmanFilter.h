#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <iostream>
#include <Eigen/Dense>

class KalmanFilter {
public:
    // 构造函数，接受Q和R作为参数
    KalmanFilter(double QQ = 1e-6, double RR = 0.01);

    // 计算方法
    void calculate(const Eigen::VectorXd& observe);

    // 获取当前状态估计值
    Eigen::VectorXd getXhat() const { return xhat; }

private:
    // 状态估计量、误差协方差等变量
    Eigen::MatrixXd Q;           // 过程噪声协方差矩阵
    Eigen::MatrixXd R;           // 测量噪声协方差矩阵
    Eigen::MatrixXd A;           // 状态转移矩阵
    Eigen::MatrixXd H;           // 测量矩阵

    Eigen::VectorXd xhat;        // 后验估计值
    Eigen::MatrixXd P;           // 后验误差协方差矩阵
    Eigen::VectorXd xhatminus;   // 先验估计值
    Eigen::MatrixXd Pminus;      // 先验误差协方差矩阵
    Eigen::MatrixXd K;           // 卡尔曼增益

};

#endif // KALMANFILTER_H
