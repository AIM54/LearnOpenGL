//
// Created by bian on 2020/10/7.
//

#include "OpencvController.h"
#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"
#include "opencv2/videoio.hpp"
#include "ijksdl_log.h"

#define OPENCV_JAVA_UTIL "com/bian/learnopengl/nativeutil/OpenCvUtil"
#define NELE(x) sizeof(x)/sizeof(x[0])

static JNINativeMethod openCvMethods[] = {
        {"loadImage",   "(Ljava/lang/String;)V", (void *) readImage},
        {"anlyisVideo", "(Ljava/lang/String;)V", (void *) readVideo}
};
using namespace cv;

void testBitMap() {
    Mat *mat = new Mat();
    mat->create(300, 900, CV_8SC4);
    delete mat;
}

void readImage(JNIEnv
               *env,
               jobject thiz, jstring
               imagePath) {
    const char *imageUrl = env->GetStringUTFChars(imagePath, 0);
    Mat imageMat = imread(imageUrl);
    ALOGI("image.rows:%d||image.cols:%d", imageMat.rows, imageMat.cols);
    env->ReleaseStringUTFChars(imagePath, imageUrl);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *jniEnv = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jclass renderClass = jniEnv->FindClass(OPENCV_JAVA_UTIL);
    if (!renderClass) {
        return JNI_ERR;
    }
    jniEnv->RegisterNatives(renderClass, openCvMethods, NELE(openCvMethods));
    jniEnv->DeleteLocalRef(renderClass);
    return JNI_VERSION_1_6;
};

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *jniEnv = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    jclass renderClass = jniEnv->FindClass(OPENCV_JAVA_UTIL);
    if (!renderClass) {
        return;
    }
    jniEnv->UnregisterNatives(renderClass);
};


void readVideo(JNIEnv
               *env,
               jobject thiz, jstring
               videoPath) {
    const char *imageUrl = env->GetStringUTFChars(videoPath, 0);
    VideoCapture videoCapture;
    if (!videoCapture.open(imageUrl)) {
        ALOGI("failed to open video");
        return;
    }
    int frameCount = videoCapture.get(cv::CAP_PROP_FRAME_COUNT);
    double videoHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
    double videoWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
    ALOGI("frameCount:%d,videoHeight:%f,videoWidth:%f", frameCount, videoHeight, videoWidth);
    videoCapture.release();
    env->ReleaseStringUTFChars(videoPath, imageUrl);
}
