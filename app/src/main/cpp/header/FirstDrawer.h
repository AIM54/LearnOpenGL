//
// Created by bian on 2020/9/3.
//

#ifndef LEARNOPENGL_FIRSTDRAWER_H
#define LEARNOPENGL_FIRSTDRAWER_H

#include "BaseRender.h"

class FirstDrawer : public BaseRender {
private:
    int mWidth;
    int mHeight;
    char *verticalShader;
    char *fragmentShader;
public:


    FirstDrawer(AAssetManager *manager);
    int initSurface(JNIEnv *jniEnv, jobject surface) override ;
    int onSizeChanged(int width, int height) override;

    int draw() override;

    GLuint glProgrem;

};


#endif //LEARNOPENGL_FIRSTDRAWER_H
