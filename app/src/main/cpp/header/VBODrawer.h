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
    GLuint vao;
    GLuint ebo[2];
protected:
    GLuint mProgram;

public:
    VBODrawer(AAssetManager *manager,
              const char *verticalPath, const char *fragmentPath);

    int initSurface(JNIEnv *jniEnv, jobject surface) override;

    int draw() override;


};


#endif //LEARNOPENGL_VBODRAWER_H
