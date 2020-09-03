//
// Created by tom1 on 2020/9/3.
//

#ifndef LEARNOPENGL_BASERENDER_H
#define LEARNOPENGL_BASERENDER_H


#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class BaseRender {
private:
    int width, height;

public:
    BaseRender(AAssetManager* assert);

    int type;

    int initSurface(jobject surface);

    int onSizeChanged(int width, int height);

    int draw();

    int destroyView();

};


#endif //LEARNOPENGL_BASERENDER_H
