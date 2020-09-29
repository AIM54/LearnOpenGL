//
// Created by tom1 on 2020/9/29.
//

#include <esUtil.h>
#include "ijksdl_log.h"
#include "EGLContextHelper.h"

void EGLContextHelper::createContext(ANativeWindow *aNativeWindow) {
    mDisPlay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mDisPlay == EGL_NO_DISPLAY) {
        return;
    }
    EGLint majarVerson, minorVerson;
    if (!eglInitialize(mDisPlay, &majarVerson, &minorVerson)) {
        return;
    }
    EGLint attribList[] =
            {
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_ALPHA_SIZE, 8,
                    EGL_DEPTH_SIZE, 24,
                    EGL_STENCIL_SIZE, 8,
                    EGL_RENDERABLE_TYPE, GetContextRenderableType(mDisPlay),
                    EGL_NONE
            };
    const EGLint MAX_CONFIG = 1;
    EGLint numConfigs;
    if (!eglChooseConfig(mDisPlay, attribList, &mDisPlay, MAX_CONFIG, &numConfigs)) {
        ALOGI("failed to pass eglChooseConfig");
        eglTerminate(mDisPlay);
        mDisPlay = EGL_NO_DISPLAY;
        return;
    }
    EGLint configs[]{
            EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
            EGL_NONE
    };

    EGLint native_virtual_id = 0;
    if (!eglGetConfigAttrib(mDisPlay, eglConfig, EGL_NATIVE_VISUAL_ID, &native_virtual_id)) {
        eglTerminate(mDisPlay);
        return ;
    }
    int32_t windowWidth = ANativeWindow_getWidth(mNativeWindow);
    int32_t windowHeight = ANativeWindow_getHeight(mNativeWindow);
    int32_t ret = ANativeWindow_setBuffersGeometry(mNativeWindow, windowWidth, windowHeight,
                                                   native_virtual_id);
    if (ret) {
        ALOGE("[EGL] ANativeWindow_setBuffersGeometry(format) returned error %d", ret);
        eglTerminate(mDisPlay);
        return ;
    }
    eglSurface = eglCreateWindowSurface(mDisPlay, eglConfig, mNativeWindow, configs);
    if (eglSurface == EGL_NO_SURFACE) {
        eglTerminate(mDisPlay);
        mDisPlay = EGL_NO_DISPLAY;
        return ;
    }

    const EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };
    eglContext = eglCreateContext(mDisPlay, eglConfig, EGL_NO_CONTEXT, contextAttribs);
    if (eglContext == EGL_NO_CONTEXT) {
        return ;
    }
    if (!eglMakeCurrent(mDisPlay, eglSurface, eglSurface, eglContext)) {
        eglDestroyContext(mDisPlay, eglContext);
        eglDestroySurface(mDisPlay, eglSurface);
        eglTerminate(mDisPlay);
        return ;
    }
}
void EGLContextHelper::destroyContext() {
    if (eglSurface) {
        eglMakeCurrent(mDisPlay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    if (eglContext) {
        eglDestroyContext(mDisPlay, eglContext);
    }
    if (eglSurface) {
        eglDestroySurface(mDisPlay, eglSurface);
    }
    if (mDisPlay) {
        eglTerminate(mDisPlay);
    }
    eglReleaseThread();
    eglContext = EGL_NO_CONTEXT;
    eglSurface = EGL_NO_SURFACE;
    mDisPlay = EGL_NO_DISPLAY;
}

