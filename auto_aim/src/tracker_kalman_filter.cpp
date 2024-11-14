#include "KalmanFilter.h"

KF::KF() : dt(0) {
    // 初始化为空值
    A = Eigen::MatrixXd::Zero(8, 8);
    x = Eigen::VectorXd::Zero(8);
    P = Eigen::MatrixXd::Identity(8, 8);
    Q = Eigen::MatrixXd::Zero(8, 8);
    R = Eigen::MatrixXd::Zero(4, 4);
    H = Eigen::MatrixXd::Zero(4, 8);
    x_ = Eigen::VectorXd::Zero(8);
    P_ = Eigen::MatrixXd::Zero(8, 8);
    K = Eigen::MatrixXd::Zero(8, 4);
}

void KF::set_dt(double dt) {
    this->dt = dt;
}

void KF::set_init(const Eigen::Vector4d& T) {
    // 设置状态转移矩阵A
    A << 1, 0, 0, 0, dt, 0, 0, 0,
         0, 1, 0, 0, 0, dt, 0, 0,
         0, 0, 1, 0, 0, 0, dt, 0,
         0, 0, 0, 1, 0, 0, 0, dt,
         0, 0, 0, 0, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 0,
         0, 0, 0, 0, 0, 0, 0, 1;

    // 设置观测矩阵H
    H << 1, 0, 0, 0, 0, 0, 0, 0,
         0, 1, 0, 0, 0, 0, 0, 0,
         0, 0, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 0, 0, 0, 0;

    // 设置测量噪声R
    double rr1 = 0.00001 * T[0];
    double rr2 = 0.00001 * T[1];
    double rr3 = 0.00001 * T[2];
    double rr4 = 0.0002;
    R = Eigen::MatrixXd(4, 4);
    R << rr1, 0, 0, 0,
         0, rr2, 0, 0,
         0, 0, rr3, 0,
         0, 0, 0, rr4;

    // 设置过程噪声Q
    double qx = 50;
    double qy = 50;
    double qz = 50;
    double qyaw = 80;
    Q << qx/4*(dt)*(dt)*(dt)*(dt), 0, 0, 0, qx/2*(dt)*(dt)*(dt), 0, 0, 0,
         0, qy/4*(dt)*(dt)*(dt)*(dt), 0, 0, 0, qy/2*(dt)*(dt)*(dt), 0, 0,
         0, 0, qz/4*(dt)*(dt)*(dt)*(dt), 0, 0, 0, qz/2*(dt)*(dt)*(dt), 0,
         0, 0, 0, qyaw/4*(dt)*(dt)*(dt)*(dt), 0, 0, 0, qyaw/2*(dt)*(dt)*(dt),
         qx/2*(dt)*(dt)*(dt), 0, 0, 0, qx*(dt)*(dt), 0, 0, 0,
         0, qy/2*(dt)*(dt)*(dt), 0, 0, 0, qy*(dt)*(dt), 0, 0,
         0, 0, qz/2*(dt)*(dt)*(dt), 0, 0, 0, qz*(dt)*(dt), 0,
         0, 0, 0, qyaw/2*(dt)*(dt)*(dt), 0, 0, 0, qyaw*(dt)*(dt);
}

void KF::set_state(const Eigen::VectorXd& x) {
    this->x = x;
}

void KF::predict() {
    x_ = A * x;
    P_ = A * P * A.transpose() + Q;
}

void KF::update(const Eigen::VectorXd& z) {
    // 卡尔曼增益计算
    K = P_ * H.transpose() * (H * P_ * H.transpose() + R).inverse();
    // 更新状态估计
    x = x_ + K * (z - H * x_);
    // 更新协方差矩阵
    P = (Eigen::MatrixXd::Identity(8, 8) - K * H) * P_;
}
