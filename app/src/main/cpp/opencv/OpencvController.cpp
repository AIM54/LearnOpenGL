//
// Created by bian on 2020/10/7.
//

#include "OpencvController.h"
#include "opencv2/opencv.hpp"

using namespace cv;

void testBitMap() {
    Mat *mat = new Mat();
    mat->create(300, 900, CV_8SC4);
    delete mat;
}