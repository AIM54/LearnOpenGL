//
// Created by tom1 on 2020/9/10.
//

#ifndef LEARNOPENGL_FIRSTVAORENDER_H
#define LEARNOPENGL_FIRSTVAORENDER_H


#include <GLES3/gl3.h>

class FirstVAORender {
private:
    GLuint mProgram;
    GLuint mVBO[2];
    GLuint mVAO;
public:
    void init(const char *vertical, const char *fragment);

    void onSizeChanged(int width, int height);

    virtual void onDraw();

    virtual ~FirstVAORender();

};


#endif //LEARNOPENGL_FIRSTVAORENDER_H
