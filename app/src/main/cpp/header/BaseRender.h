//
// Created by tom1 on 2020/9/3.
//

#ifndef LEARNOPENGL_BASERENDER_H
#define LEARNOPENGL_BASERENDER_H


#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <ijksdl_log.h>

extern "C" {
#include "AssetReader.h"
#include "esUtil.h"
};

class BaseRender {
protected:
    EGLSurface eglSurface;
    EGLDisplay eglDisplay;
private:
    int width, height;
    EGLConfig eglConfig;
    ANativeWindow *mNativeWindow;
    EGLContext eglContext;
    int type;
public:

    BaseRender(AAssetManager *manager);

    virtual ~BaseRender();

    virtual int initSurface(JNIEnv *jniEnv, jobject surface);

    virtual int onSizeChanged(int width, int height) = 0;

    virtual int draw() = 0;

    virtual int destroyView();


};


#endif //LEARNOPENGL_BASERENDER_H
