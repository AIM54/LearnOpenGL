//
// Created by tom1 on 2020/10/26.
//

#ifndef LEARNOPENGL_OPENCVDRAWER_H
#define LEARNOPENGL_OPENCVDRAWER_H

#include "NewBaseRender.h"
#define  VERTEX_POS_INDEX 0
#define  VERTEX_POS_SIZE  3

#define  COLOR_POS_INDEX  1
#define  COLOR_POS_SIZE   4


#define  TEX_POS_INDEX  2
#define  TEX_POS_SIZE   2


#define  VERTEX_STRIDE (sizeof(GLfloat)*(VERTEX_POS_SIZE+COLOR_POS_SIZE+TEX_POS_SIZE))
class OpenCvDrawer : public NewBaseRender {
public:
    OpenCvDrawer(AAssetManager *manager,
                 const char *imagePath);

    ~OpenCvDrawer();

    int initSurface(JNIEnv *jniEnv, jobject surface) override;

protected:
    void onDraw(float deltaTime) override;

private:
    char *verticalShader;
    char *fragmentShader;
    char *mImagePath;
    GLuint mProgram;
    GLuint mVBO[2];
    GLuint mVAO;
    GLuint texture1;

};


#endif //LEARNOPENGL_OPENCVDRAWER_H
