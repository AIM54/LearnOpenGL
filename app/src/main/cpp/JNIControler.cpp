//
// Created by tom1 on 2020/9/1.
//
#include <jni.h>
#include <android/log.h>
#include <ijksdl_log.h>

#define MY_OPENGL_RENDER  "com/bian/learnopengl/nativeutil/MyRender"

static JNINativeMethod renderMethods[] = {
        {}
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *jniEnv = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        ALOGE("failed to get env");
    }
    ALOGE("className is :%s", MY_OPENGL_RENDER);
    jclass renderClass = jniEnv->FindClass(MY_OPENGL_RENDER);
    if (!renderClass) {
        ALOGE("failed to find class:%s", MY_OPENGL_RENDER);
    }
    return JNI_VERSION_1_6;
};

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
};


