//
// Created by bian on 2020/9/6.
//

#ifndef LEARNOPENGL_VBODRAWER_H
#define LEARNOPENGL_VBODRAWER_H


#include "BaseRender.h"

class VBODrawer : public BaseRender {
private:
    char *verticalShader;

    char *fragmentShader;
    GLuint mVAO;
    GLuint mVBO[2];
protected:
    GLuint mProgram;

public:
    VBODrawer(AAssetManager *manager,
              const char *verticalPath, const char *fragmentPath);

    int initSurface(JNIEnv *jniEnv, jobject surface) override;

    int draw() override;

    int destroyView() override;
    virtual ~VBODrawer();
};


#endif //LEARNOPENGL_VBODRAWER_H