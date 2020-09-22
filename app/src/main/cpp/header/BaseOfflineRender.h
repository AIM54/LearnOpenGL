//
// Created by tom1 on 2020/9/21.
//

#ifndef LEARNOPENGL_BASEOFFLINERENDER_H
#define LEARNOPENGL_BASEOFFLINERENDER_H

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <KHR/khrplatform.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

typedef uint8_t Byte;

class BaseOfflineRender {

public:
    BaseOfflineRender(AAssetManager *manager);

    void draw();

    virtual void onDestroy();

    virtual ~BaseOfflineRender();

    void setImageCallBack(void (*imageCallback)(Byte *));
protected:
    EGLDisplay pbuDisplay;
    EGLSurface pubSurface;
    EGLContext eglContext;
    int width, height;
    void (*PixCallBack)(Byte *imageData);
    virtual void initProgram() = 0;
    virtual void onDraw() = 0;
};


#endif //LEARNOPENGL_BASEOFFLINERENDER_H
