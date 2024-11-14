// /include/Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <unistd.h>
#include "MvCameraControl.h"

extern bool g_bExit;
extern cv::Mat g_image;
extern pthread_mutex_t g_mutex;

class Camera {
public:
    void* handle;
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    unsigned int nPayloadSize;

    // 构造函数：初始化摄像头
    Camera(const std::string& deviceIp, const std::string& netIp);
    
    // 析构函数：释放资源
    ~Camera();

    // IP地址解析函数
    static void parseIp(const std::string& ip, unsigned int& parsedIp);

    // 摄像头取流线程
    static void* workThread(void* pUser);

        // 设置曝光时间（单位：微秒）
    bool setExposureTime(float exposureTime) {
        int nRet = MV_CC_SetFloatValue(handle, "ExposureTime", exposureTime);
        return (nRet == MV_OK);
    }
    
    // 设置增益
    bool setGain(float gain) {
        int nRet = MV_CC_SetFloatValue(handle, "Gain", gain);
        return (nRet == MV_OK);
    }
    
    // 获取当前曝光时间
    float getExposureTime() {
        MVCC_FLOATVALUE stValue = {0};
        int nRet = MV_CC_GetFloatValue(handle, "ExposureTime", &stValue);
        if (nRet == MV_OK) {
            return stValue.fCurValue;
        }
        return -1.0f;
    }
    
    // 获取当前增益
    float getGain() {
        MVCC_FLOATVALUE stValue = {0};
        int nRet = MV_CC_GetFloatValue(handle, "Gain", &stValue);
        if (nRet == MV_OK) {
            return stValue.fCurValue;
        }
        return -1.0f;
    }

};

#endif // CAMERA_H
