#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <Eigen/Dense>

class KF {
public:
    // 构造函数
    KF();

    // 设置时间间隔
    void set_dt(double dt);

    // 设置初始值
    void set_init(const Eigen::Vector4d& T);

    // 设置初始状态
    void set_state(const Eigen::VectorXd& x);

    // 预测步骤
    void predict();

    // 更新步骤
    void update(const Eigen::VectorXd& z);

    // 获取当前状态估计值
    Eigen::VectorXd get_state() const { return x; }

private:
    Eigen::MatrixXd A;   // 状态转移矩阵
    Eigen::VectorXd x;   // 当前状态
    Eigen::MatrixXd P;   // 后验协方差矩阵
    Eigen::MatrixXd Q;   // 过程噪声协方差矩阵
    Eigen::MatrixXd R;   // 测量噪声协方差矩阵
    Eigen::MatrixXd H;   // 观测矩阵
    Eigen::VectorXd x_;  // 预测状态
    Eigen::MatrixXd P_;  // 预测协方差矩阵
    Eigen::MatrixXd K;   // 卡尔曼增益
    double dt;           // 时间间隔
};

#endif // KALMANFILTER_H
