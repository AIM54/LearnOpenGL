//
// Created by tom1 on 2020/9/7.
//

#ifndef LEARNOPENGL_PICTUREDRAWER_H
#define LEARNOPENGL_PICTUREDRAWER_H


#include "BaseRender.h"
#include "png.h"
class PictureDrawer : public BaseRender {
private:
    uint8_t *imageData;
    char *verticalShader;
    char *fragmentShader;
    GLuint mProgram;
    GLuint mVBO[2];
    GLuint mVAO;
    GLuint texture1;

    png_uint_32 image_width;
    png_uint_32 image_height;
public:
    PictureDrawer(AAssetManager *manager,
                  const char *imagePath);

    int draw() override;


    int initSurface(JNIEnv *jniEnv, jobject surface) override;


};


#endif //LEARNOPENGL_PICTUREDRAWER_H
