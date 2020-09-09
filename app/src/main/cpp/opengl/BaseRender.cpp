//
// Created by tom1 on 2020/9/3.
//



#include "gl3stub.h"
#include "BaseRender.h"

BaseRender::BaseRender(AAssetManager *manager) {

}

int BaseRender::onSizeChanged(int width, int height) {
    this->width = width;
    this->height = height;
    return GL_TRUE;
}

int BaseRender::getWidth() {
    return width;
}

int BaseRender::getHeight() {
    return height;
}

int BaseRender::initSurface(JNIEnv *jniEnv, jobject surface) {
    if (!gl3stubInit()) {
        return GL_FALSE;
    }
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        ALOGI("faild to get display");
        return EGL_FALSE;
    }
    EGLint majarVersion;
    EGLint minorVersion;
    if (!eglInitialize(eglDisplay, &majarVersion, &minorVersion)) {
        ALOGE("failed to init eglDisplay");
        eglDisplay = EGL_NO_DISPLAY;
        return EGL_FALSE;
    }

    ALOGI("majarVersion:%d,minorVersion:%d", majarVersion, minorVersion);

    EGLint attribList[] =
            {
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_DEPTH_SIZE, 24,
                    EGL_STENCIL_SIZE, 8,
                    EGL_RENDERABLE_TYPE, GetContextRenderableType(eglDisplay),
                    EGL_NONE
            };
    const EGLint MAX_CONFIG = 1;
    EGLint numConfigs;
    if (!eglChooseConfig(eglDisplay, attribList, &eglConfig, MAX_CONFIG, &numConfigs)) {
        ALOGI("failed to pass eglChooseConfig");
        eglTerminate(eglDisplay);
        eglDisplay = EGL_NO_DISPLAY;
        return EGL_FALSE;
    }
    mNativeWindow = ANativeWindow_fromSurface(jniEnv, surface);
    EGLint configs[]{
            EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
            EGL_NONE
    };

    EGLint native_virtual_id = 0;
    if (!eglGetConfigAttrib(eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &native_virtual_id)) {
        eglTerminate(eglDisplay);
        return EGL_FALSE;
    }
    int32_t windowWidth = ANativeWindow_getWidth(mNativeWindow);
    int32_t windowHeight = ANativeWindow_getHeight(mNativeWindow);
    int32_t ret = ANativeWindow_setBuffersGeometry(mNativeWindow, windowWidth, windowHeight,
                                                   native_virtual_id);
    if (ret) {
        ALOGE("[EGL] ANativeWindow_setBuffersGeometry(format) returned error %d", ret);
        eglTerminate(eglDisplay);
        return EGL_FALSE;
    }
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, mNativeWindow, configs);
    if (eglSurface == EGL_NO_SURFACE) {
        eglTerminate(eglDisplay);
        eglDisplay = EGL_NO_DISPLAY;
        return EGL_FALSE;
    }

    const EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };

    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if (eglContext == EGL_NO_CONTEXT) {
        return EGL_FALSE;
    }
    if (!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext)) {
        eglDestroyContext(eglDisplay, eglContext);
        eglDestroySurface(eglDisplay, eglSurface);
        eglTerminate(eglDisplay);
        return EGL_FALSE;
    }
    ALOGI("after initSurface");
    return EGL_TRUE;
}

int BaseRender::destroyView() {
    if (eglSurface) {
        eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    if (eglContext) {
        eglDestroyContext(eglDisplay, eglContext);
    }
    if (eglSurface) {
        eglDestroySurface(eglDisplay, eglSurface);
    }
    if (eglDisplay) {
        eglTerminate(eglDisplay);
    }
    eglReleaseThread();
    eglContext = EGL_NO_CONTEXT;
    eglSurface = EGL_NO_SURFACE;
    eglDisplay = EGL_NO_DISPLAY;
    return GL_TRUE;
}

BaseRender::~BaseRender() {

}