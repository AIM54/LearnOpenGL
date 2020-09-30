//
// Created by tom1 on 2020/9/29.
//

#ifndef LEARNOPENGL_EGLCONTEXTHELPER_H
#define LEARNOPENGL_EGLCONTEXTHELPER_H

#include <android/window.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>
#include <GLES3/gl32.h>

class EGLContextHelper {
public:
    void createContext(ANativeWindow *aNativeWindow);

    void destroyContext();

protected:

    EGLDisplay mDisPlay;
    EGLConfig eglConfig;
    ANativeWindow *mNativeWindow;
    EGLSurface eglSurface;
    EGLContext eglContext;
};


#endif //LEARNOPENGL_EGLCONTEXTHELPER_H
