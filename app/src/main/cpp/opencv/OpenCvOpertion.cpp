//
// Created by tom1 on 2020/10/21.
//
#include <opencv2/core/types_c.h>
#include "OpenCvOpertion.h"
#include "opencv2/opencv.hpp"
#include "ijksdl_log.h"
#include "iostream"

using namespace cv;
//将图片的蓝色值点到最亮
void turnPictureToGreyPic(const char *filePath) {
    ALOGI("filePath is :%s", filePath);
    Mat imageMat = imread(filePath);
    if (imageMat.empty()) {
        ALOGI("failed to read my funcation");
        return;
    }
    for (int i = 0; i < imageMat.rows; i++) {
        for (int j = 0; j < imageMat.cols; j++) {
            imageMat.at<Vec3b>(i, j)[0] = 255;
        }
    }
    ALOGI("after turnPictureToGreyPic");
    imwrite("/storage/emulated/0/Pictures/moon123.png", imageMat);
    ALOGI("after savePicture");
}

