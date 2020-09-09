//
// Created by bian on 2020/9/5.
//

#include "FirstDrawer.h"

FirstDrawer::FirstDrawer(AAssetManager *manager) : BaseRender(manager) {
    verticalShader = readStringFromAssert(manager, "FirstVerticalShader.glsl");
    fragmentShader = readStringFromAssert(manager, "FirstFragmentShader.glsl");
}

int FirstDrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    int result = BaseRender::initSurface(jniEnv, surface);
    if (!result) {
        return result;
    }
    glProgrem = esLoadProgram(verticalShader, fragmentShader);
    free(verticalShader);
    free(fragmentShader);
    return result;
}

int FirstDrawer::draw() {
    if (!glProgrem) {
        ALOGI("failed to create glProgram");
        return GL_FALSE;
    }
    GLfloat vVertexts[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
    glUseProgram(glProgrem);
    glViewport(0, 0, getWidth(), getHeight());
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertexts);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    eglSwapBuffers(eglDisplay, eglSurface);
    return GL_TRUE;
}

