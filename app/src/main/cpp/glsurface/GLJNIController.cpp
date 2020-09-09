//
// Created by tom1 on 2020/9/1.
//
#include <jni.h>
#include <android/log.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <ijksdl_log.h>
#include "gl3stub.h"
#include "GLJNIController.h"

extern "C" {
}
static JNINativeMethod renderMethods[] = {
        {"onSurfaceCreated", "()V",   (void *) onSurfaceCreated},
        {"onDrawFrame",      "()V",   (void *) onDrawFrame},
        {"onSurfaceChanged", "(II)V", (void *) onSurfaceChanged},
};

#define MY_OPENGL_RENDER  "com/bian/learnopengl/nativeutil/GLSurfaceViewRender"

#define NELE(x) sizeof(x)/sizeof(x[0])

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *jniEnv = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    ALOGE("className is :%s", MY_OPENGL_RENDER);
    jclass renderClass = jniEnv->FindClass(MY_OPENGL_RENDER);
    if (!renderClass) {
        ALOGE("failed to find class:%s", MY_OPENGL_RENDER);
        return JNI_ERR;
    }
    ALOGE("renderMethods.length is :%d", NELE(renderMethods));
    jniEnv->RegisterNatives(renderClass, renderMethods, NELE(renderMethods));
    jniEnv->DeleteLocalRef(renderClass);
    return JNI_VERSION_1_6;
};

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *jniEnv = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        ALOGE("failed to get env");
        return;
    }
    jclass renderClass = jniEnv->FindClass(MY_OPENGL_RENDER);
    if (!renderClass) {
        ALOGE("failed to find class:%s", MY_OPENGL_RENDER);
        return;
    }
    jniEnv->UnregisterNatives(renderClass);

};
void onSurfaceCreated(JNIEnv
                      *env,
                      jobject thiz
){

}

void onSurfaceChanged(JNIEnv
                      *env,
                      jobject thiz,
                      jint
                      width,
                      jint height
){

}

void onDrawFrame(JNIEnv
                 *env,
                 jobject thiz
){

}