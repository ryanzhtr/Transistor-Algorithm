#include "KalmanFilter.h"
#include <Eigen/Dense>

KalmanFilter::KalmanFilter(double QQ, double RR) {
    // 初始化矩阵和向量
    Q = QQ * Eigen::MatrixXd::Identity(3, 3);  // 过程噪声协方差矩阵
    R = RR * Eigen::MatrixXd::Identity(3, 3);  // 测量噪声协方差矩阵
    A = Eigen::MatrixXd::Identity(3, 3);        // 状态转移矩阵
    H = Eigen::MatrixXd::Identity(3, 3);        // 测量矩阵

    xhat = Eigen::VectorXd::Zero(3);            // 后验状态估计
    P = Eigen::MatrixXd::Zero(3, 3);            // 后验误差协方差
    xhatminus = Eigen::VectorXd::Zero(3);       // 先验状态估计
    Pminus = Eigen::MatrixXd::Zero(3, 3);       // 先验误差协方差
    K = Eigen::MatrixXd::Zero(3, 3);            // 卡尔曼增益
}

void KalmanFilter::calculate(const Eigen::VectorXd& observe) {
    // 时间更新
    xhatminus = A * xhat;  // 先验状态估计: X(k|k-1) = A * X(k-1|k-1)
    Pminus = A * P * A.transpose() + Q;  // 先验误差协方差: P(k|k-1) = A * P(k-1|k-1) * A' + Q

    // 测量更新
    K = Pminus * H.transpose() * (H * Pminus * H.transpose() + R).inverse();  // 卡尔曼增益
    xhat = xhatminus + K * (observe - H * xhatminus);  // 后验状态估计: X(k|k) = X(k|k-1) + K * (Z(k) - H * X(k|k-1))
    P = (Eigen::MatrixXd::Identity(3, 3) - K * H) * Pminus;  // 后验误差协方差: P(k|k) = (I - K * H) * P(k|k-1)
}

