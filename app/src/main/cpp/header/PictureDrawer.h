//
// Created by tom1 on 2020/9/7.
//

#ifndef LEARNOPENGL_PICTUREDRAWER_H
#define LEARNOPENGL_PICTUREDRAWER_H


#include "BaseRender.h"

class PictureDrawer : BaseRender {
public:
    PictureDrawer(AAssetManager *manager,
                  const char *verticalPath, const char *fragmentPath,
                  const char *imagePath);

    int draw() override;

    int initSurface(JNIEnv *jniEnv, jobject surface) override;

};


#endif //LEARNOPENGL_PICTUREDRAWER_H
