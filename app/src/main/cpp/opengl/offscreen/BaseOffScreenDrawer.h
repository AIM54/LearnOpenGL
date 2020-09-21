//
// Created by tom1 on 2020/9/21.
//

#ifndef LEARNOPENGL_BASEOFFSCREENDRAWER_H
#define LEARNOPENGL_BASEOFFSCREENDRAWER_H

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#include <KHR/khrplatform.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class BaseOffScreenDrawer {

public:
    BaseOffScreenDrawer(AAssetManager *manager);
    void draw();
    void destroyView();

protected:
    virtual void onDestroy();

    virtual void initProgram() = 0;

    virtual void onDraw() = 0;

    EGLDisplay pbuDisplay;
    EGLSurface pubSurface;
    EGLContext eglContext;
};


#endif //LEARNOPENGL_BASEOFFSCREENDRAWER_H
