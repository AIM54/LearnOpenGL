//
// Created by bian on 2020/10/7.
//

#include "OpencvController.h"

#include "ijksdl_log.h"
#include "OpenCvOpertion.h"

#define OPENCV_JAVA_UTIL "com/bian/learnopengl/nativeutil/OpenCvUtil"
#define NELE(x) sizeof(x)/sizeof(x[0])

static JNINativeMethod openCvMethods[] = {
        {"loadImage", "(Ljava/lang/String;)V", (void *) readImage},
};

void readImage(JNIEnv
               *env,
               jobject thiz, jstring
               imagePath) {
    const char *imageUrl = env->GetStringUTFChars(imagePath, 0);
    turnPictureToGreyPic(imageUrl);
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