//
// Created by tom1 on 2020/9/1.
//
#include <jni.h>

#define MY_OPENGL_RENDER "com\bian\learnopengl\nativeutil\MyRender"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    return JNI_VERSION_1_6;
};

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
};


