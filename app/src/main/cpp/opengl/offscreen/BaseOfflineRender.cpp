//
// Created by tom1 on 2020/9/21.
//

#include <ijksdl_log.h>
#include "BaseOfflineRender.h"

BaseOfflineRender::BaseOfflineRender(AAssetManager *manager) {
    eglContext = EGL_NO_CONTEXT;
    pbuDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLint majarVersion;
    EGLint minorVersion;
    if (!eglInitialize(pbuDisplay, &majarVersion, &minorVersion)) {
        ALOGE("failed to init eglDisplay");
        pbuDisplay = EGL_NO_DISPLAY;
        return;
    }
    EGLint attribList[] = {
            EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
            EGL_RED_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,// if you need the depth buffer
            EGL_STENCIL_SIZE,8,
            EGL_NONE
    };
    const EGLint MAX_CONFIG = 1;
    EGLConfig config;
    EGLint numConfigs;
    if (!eglChooseConfig(pbuDisplay, attribList, &config, MAX_CONFIG, &numConfigs)) {
        eglTerminate(pbuDisplay);
        return;
    }
    width = 720;
    height = 1080;
    EGLint screenList[] = {
            EGL_WIDTH, 1,
            EGL_HEIGHT, 1,
            EGL_NONE
    };
    ALOGI("before eglCreatePbufferSurface");
    pubSurface = eglCreatePbufferSurface(pbuDisplay, config, screenList);

    if (pubSurface == EGL_NO_SURFACE) {
        switch (glGetError()) {
            case EGL_BAD_ALLOC:
                ALOGE("EGL_BAD_ALLOC");
                break;
            case EGL_BAD_CONFIG:
                ALOGE("EGL_BAD_CONFIG");
                break;
            case EGL_BAD_PARAMETER:
                ALOGE("EGL_BAD_PARAMETER");
                break;
            case EGL_BAD_MATCH:
                ALOGE("EGL_BAD_MATCH");
                break;
            case EGL_BAD_DISPLAY:
                ALOGE("EGL_BAD_DISPLAY");
                break;
        }
        eglTerminate(pbuDisplay);
        return;
    }
    ALOGI("after eglCreatePbufferSurface");
    const EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };

    eglContext = eglCreateContext(pbuDisplay, config, EGL_NO_CONTEXT, contextAttribs);

    if (eglContext == EGL_NO_CONTEXT) {
        eglDestroySurface(pbuDisplay, pubSurface);
        eglTerminate(pbuDisplay);
        return;
    }
    ALOGI("after eglCreateContext");
    if (!eglMakeCurrent(pbuDisplay, pubSurface, pubSurface, eglContext)) {
        eglDestroyContext(pbuDisplay, eglContext);
        eglDestroySurface(pbuDisplay, pubSurface);
        eglTerminate(pbuDisplay);
        eglContext = EGL_NO_CONTEXT;
        return;
    }
}


void BaseOfflineRender::draw() {
    if (eglContext != EGL_NO_CONTEXT) {
        onDraw();
    }
}

void BaseOfflineRender::onDestroy() {
    if (pubSurface) {
        eglMakeCurrent(pbuDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    if (eglContext) {
        eglDestroyContext(pbuDisplay, eglContext);
    }
    if (pubSurface) {
        eglDestroySurface(pbuDisplay, pubSurface);
    }
    if (pbuDisplay) {
        eglTerminate(pbuDisplay);
    }
    eglReleaseThread();
    eglContext = EGL_NO_CONTEXT;
    pubSurface = EGL_NO_SURFACE;
    pbuDisplay = EGL_NO_DISPLAY;
}

void BaseOfflineRender::setImageCallBack(void (*imageCallback)(Byte *)) {
    this->PixCallBack = imageCallback;
}

BaseOfflineRender::~BaseOfflineRender() {

}



