//
// Created by tom1 on 2020/10/26.
//

#include "OpenCvDrawer.h"
#include "opencv2/opencv.hpp"
#include "ijksdl_log.h"

using namespace cv;

OpenCvDrawer::OpenCvDrawer(AAssetManager *manager,
                           const char *imagePath) : NewBaseRender(manager) {
    ALOGI("OpenCvDrawer::OpenCvDrawer(AAssetManager *manager,const char *imagePath)");
    Mat imgPic = imread(imagePath);
    if (imgPic.empty()) {
        return;
    }
    imgPic.data;
}

void OpenCvDrawer::onDraw(float deltaTime) {
}