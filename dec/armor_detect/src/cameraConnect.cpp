// #include "Camera.h"
// #include <opencv2/opencv.hpp>
// #include <pthread.h>
// #include <iostream>
// #include <cstdlib>
// #include <cstring>

// bool g_bExit = false;
// cv::Mat g_image;
// pthread_mutex_t g_mutex;

// Camera::Camera(const std::string& deviceIp, const std::string& netIp) {
//     int nRet = MV_OK;

//     // 初始化SDK
//     nRet = MV_CC_Initialize();
//     if (MV_OK != nRet) {
//         std::cerr << "Initialize SDK fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
//         exit(1);
//     } else {
//         std::cout << "SDK initialized successfully." << std::endl;
//     }

//     MV_CC_DEVICE_INFO stDevInfo;
//     MV_GIGE_DEVICE_INFO stGigEDev;

//     // 解析IP地址
//     parseIp(deviceIp, stGigEDev.nCurrentIp);
//     parseIp(netIp, stGigEDev.nNetExport);
//     std::cout << "Device IP and Net IP parsed successfully." << std::endl;

//     stDevInfo.nTLayerType = MV_GIGE_DEVICE;
//     stDevInfo.SpecialInfo.stGigEInfo = stGigEDev;

//     // 创建句柄
//     handle = NULL;
//     nRet = MV_CC_CreateHandle(&handle, &stDevInfo);
//     if (MV_OK != nRet) {
//         std::cerr << "Create Handle fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
//         exit(1);
//     } else {
//         std::cout << "Handle created successfully." << std::endl;
//     }

//     // 打开设备
//     nRet = MV_CC_OpenDevice(handle);
//     if (MV_OK != nRet) {
//         std::cerr << "Open device fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
//         exit(1);
//     } else {
//         std::cout << "Device opened successfully." << std::endl;
//     }

//     // 获取 GigE 相机的最佳数据包大小
//     int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
//     if (nPacketSize > 0) {
//         nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
//         if (MV_OK != nRet) {
//             std::cerr << "Set Packet Size fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
//         } else {
//             std::cout << "Optimal packet size set successfully." << std::endl;
//         }
//     }

//     // 启用自动曝光
//     MV_CC_SetEnumValue(handle, "ExposureAuto", 1);  // 1: 自动曝光
//     std::cout << "Auto exposure enabled." << std::endl;

//     // 启用自动增益
//     MV_CC_SetEnumValue(handle, "GainAuto", 1);  // 1: 自动增益
//     std::cout << "Auto gain enabled." << std::endl;

//     // 启用白平衡自动
//     MV_CC_SetEnumValue(handle, "BalanceWhiteAuto", 1);  // 1: 自动白平衡
//     std::cout << "Auto white balance enabled." << std::endl;

//     // 获取数据包大小
//     MVCC_INTVALUE stParam;
//     memset(&stParam, 0, sizeof(MVCC_INTVALUE));
//     nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
//     if (MV_OK != nRet) {
//         std::cerr << "Get PayloadSize fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
//         exit(1);
//     } else {
//         std::cout << "Payload size: " << stParam.nCurValue << std::endl;
//     }
//     nPayloadSize = stParam.nCurValue;

//     // 开始取流
//     nRet = MV_CC_StartGrabbing(handle);
//     if (MV_OK != nRet) {
//         std::cerr << "Start grabbing fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
//         exit(1);
//     } else {
//         std::cout << "Grabbing started successfully." << std::endl;
//     }

//     // 启动取流线程
//     pthread_t grabThread;
//     pthread_create(&grabThread, NULL, workThread, this);
//     std::cout << "Grabbing thread started." << std::endl;
// }

// Camera::~Camera() {
//     // 停止取流
//     MV_CC_StopGrabbing(handle);
//     std::cout << "Grabbing stopped." << std::endl;

//     // 关闭设备
//     MV_CC_CloseDevice(handle);
//     std::cout << "Device closed." << std::endl;

//     // 销毁句柄
//     MV_CC_DestroyHandle(handle);
//     std::cout << "Handle destroyed." << std::endl;

//     // 释放SDK资源
//     MV_CC_Finalize();
//     std::cout << "SDK finalized." << std::endl;
// }

// void Camera::parseIp(const std::string& ip, unsigned int& parsedIp) {
//     int parts[4];
//     sscanf(ip.c_str(), "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]);
//     parsedIp = (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3];
//     std::cout << "Parsed IP: " << ip << std::endl;
// }

// void* Camera::workThread(void* pUser) {
//     Camera* pCam = (Camera*)pUser;
//     MV_FRAME_OUT_INFO_EX stImageInfo;
//     memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));

//     unsigned char* pData = (unsigned char*)malloc(pCam->nPayloadSize);
//     if (pData == NULL) {
//         std::cerr << "Allocate memory fail!" << std::endl;
//         return NULL;
//     } else {
//         std::cout << "Memory allocated for frame data." << std::endl;
//     }

//     while (!g_bExit) {
//         int nRet = MV_CC_GetOneFrameTimeout(pCam->handle, pData, pCam->nPayloadSize, &stImageInfo, 1000);
//         if (nRet == MV_OK) {
//             std::cout << "Frame received: Width[" << stImageInfo.nWidth << "], Height[" << stImageInfo.nHeight << "]" << std::endl;

//             if (stImageInfo.nFrameLen != pCam->nPayloadSize) {
//                 std::cerr << "Frame data length mismatch! Expected: " << pCam->nPayloadSize << ", Received: " << stImageInfo.nFrameLen << std::endl;
//                 continue;
//             }

//             // 打印图像数据的前几个像素，查看数据是否合理
//             std::cout << "First few pixel values: ";
//             for (int i = 0; i < 10; ++i) {
//                 std::cout << (int)pData[i] << " ";
//             }
//             std::cout << std::endl;

//             if (stImageInfo.enPixelType == PixelType_Gvsp_BayerGB8) {
//                 cv::Mat img(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC1, pData);

//                 // 显示原始的BayerGB8图像数据
//                 cv::imshow("Raw Bayer Image", img);
//                 cv::waitKey(1);

//                 // 转换为BGR格式
//                 cv::Mat bgrImg;
//                 cv::cvtColor(img, bgrImg, cv::COLOR_BayerGB2BGR);

//                 pthread_mutex_lock(&g_mutex);
//                 g_image = bgrImg.clone();  // 更新图像
//                 pthread_mutex_unlock(&g_mutex);

//                 std::cout << "BayerGB8 image updated." << std::endl;

//                 cv::imshow("Captured Frame", bgrImg);
//                 cv::waitKey(1);  // 刷新窗口
//             } else {
//                 std::cerr << "Unsupported pixel format: " << stImageInfo.enPixelType << std::endl;
//             }
//         } else {
//             // 捕获失败时的处理
//             //std::cerr << "No frame data received! ret [0x" << std::hex << nRet << "]" << std::endl;
//         }

//         if (g_bExit) {
//             break;
//         }
//     }

//     free(pData);
//     std::cout << "Frame grabbing thread exiting." << std::endl;
//     return NULL;
// }

#include "Camera.h"

bool g_bExit = false;
cv::Mat g_image;
pthread_mutex_t g_mutex;

Camera::Camera(const std::string& deviceIp, const std::string& netIp) {
    int nRet = MV_OK;

    // 初始化SDK
    nRet = MV_CC_Initialize();
    if (MV_OK != nRet) {
        std::cerr << "Initialize SDK fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
        exit(1);
    } else {
        std::cout << "SDK initialized successfully." << std::endl;
    }

    MV_CC_DEVICE_INFO stDevInfo;
    MV_GIGE_DEVICE_INFO stGigEDev;

    // 解析IP地址
    parseIp(deviceIp, stGigEDev.nCurrentIp);
    parseIp(netIp, stGigEDev.nNetExport);
    std::cout << "Device IP and Net IP parsed successfully." << std::endl;

    stDevInfo.nTLayerType = MV_GIGE_DEVICE;
    stDevInfo.SpecialInfo.stGigEInfo = stGigEDev;

    // 创建句柄
    handle = NULL;
    nRet = MV_CC_CreateHandle(&handle, &stDevInfo);
    if (MV_OK != nRet) {
        std::cerr << "Create Handle fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
        exit(1);
    } else {
        std::cout << "Handle created successfully." << std::endl;
    }

    // 打开设备
    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK != nRet) {
        std::cerr << "Open device fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
        exit(1);
    } else {
        std::cout << "Device opened successfully." << std::endl;
    }

    // 获取 GigE 相机的最佳数据包大小
    int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
    if (nPacketSize > 0) {
        nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
        if (MV_OK != nRet) {
            std::cerr << "Set Packet Size fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
        } else {
            std::cout << "Optimal packet size set successfully." << std::endl;
        }
    }

    // 禁用自动曝光
    MV_CC_SetEnumValue(handle, "ExposureAuto", 0);
    std::cout << "Auto exposure disabled." << std::endl;

    // 禁用自动增益
    MV_CC_SetEnumValue(handle, "GainAuto", 0);
    std::cout << "Auto gain disabled." << std::endl;

    // 禁用白平衡自动
    MV_CC_SetEnumValue(handle, "BalanceWhiteAuto", 0);
    std::cout << "Auto white balance disabled." << std::endl;

    // 获取数据包大小
    MVCC_INTVALUE stParam;
    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
    if (MV_OK != nRet) {
        std::cerr << "Get PayloadSize fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
        exit(1);
    } else {
        std::cout << "Payload size: " << stParam.nCurValue << std::endl;
    }
    nPayloadSize = stParam.nCurValue;

    // 开始取流
    nRet = MV_CC_StartGrabbing(handle);
    if (MV_OK != nRet) {
        std::cerr << "Start grabbing fail! nRet [0x" << std::hex << nRet << "]" << std::endl;
        exit(1);
    } else {
        std::cout << "Grabbing started successfully." << std::endl;
    }

    // 启动取流线程
    pthread_t grabThread;
    pthread_create(&grabThread, NULL, workThread, this);
    std::cout << "Grabbing thread started." << std::endl;
}

Camera::~Camera() {
    // 停止取流
    MV_CC_StopGrabbing(handle);
    std::cout << "Grabbing stopped." << std::endl;

    // 关闭设备
    MV_CC_CloseDevice(handle);
    std::cout << "Device closed." << std::endl;

    // 销毁句柄
    MV_CC_DestroyHandle(handle);
    std::cout << "Handle destroyed." << std::endl;

    // 释放SDK资源
    MV_CC_Finalize();
    std::cout << "SDK finalized." << std::endl;
}

void Camera::parseIp(const std::string& ip, unsigned int& parsedIp) {
    int parts[4];
    sscanf(ip.c_str(), "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]);
    parsedIp = (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3];
    std::cout << "Parsed IP: " << ip << std::endl;
}

void* Camera::workThread(void* pUser) {
    Camera* pCam = (Camera*)pUser;
    MV_FRAME_OUT_INFO_EX stImageInfo;
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));

    unsigned char* pData = (unsigned char*)malloc(pCam->nPayloadSize);
    if (pData == NULL) {
        std::cerr << "Allocate memory fail!" << std::endl;
        return NULL;
    } else {
        std::cout << "Memory allocated for frame data." << std::endl;
    }

    while (!g_bExit) {
        int nRet = MV_CC_GetOneFrameTimeout(pCam->handle, pData, pCam->nPayloadSize, &stImageInfo, 5000);
        if (nRet == MV_OK) {
            std::cout << "Frame received: Width[" << stImageInfo.nWidth << "], Height[" << stImageInfo.nHeight << "]" << std::endl;

            // 检查帧数据完整性
            if (stImageInfo.nFrameLen != pCam->nPayloadSize) {
                std::cerr << "Frame data length mismatch! Expected: " << pCam->nPayloadSize << ", Received: " << stImageInfo.nFrameLen << std::endl;
                continue; // 跳过本次循环
            }

            // 检查源像素类型
            std::cout << "Source Pixel Type: " << stImageInfo.enPixelType << std::endl;

            // 处理 BayerGB8 格式
            if (stImageInfo.enPixelType == PixelType_Gvsp_BayerGB8) {
                cv::Mat img(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC1, pData);  // 单通道 BayerGB8
                cv::Mat bgrImg;
                cv::cvtColor(img, bgrImg, cv::COLOR_BayerGB2BGR);  // 转换为 BGR 格式

                // 显示原始 Bayer 图像
                cv::imshow("Raw Bayer Image", img);

                // 线程锁定，更新图像
                pthread_mutex_lock(&g_mutex);
                g_image = bgrImg.clone();  // 将转换后的 BGR 图像保存
                pthread_mutex_unlock(&g_mutex);

                std::cout << "BayerGB8 image updated." << std::endl;
            } else {
                std::cerr << "Unsupported pixel format: " << stImageInfo.enPixelType << std::endl;
            }
        } else {
            //std::cerr << "No frame data received! ret [0x" << std::hex << nRet << "]" << std::endl;
        }

        if (g_bExit) {
            break;
        }
    }

    free(pData);
    std::cout << "Frame grabbing thread exiting." << std::endl;
    return NULL;
}
