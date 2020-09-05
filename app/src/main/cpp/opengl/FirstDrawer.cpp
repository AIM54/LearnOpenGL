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
    glProgrem = esLoadProgram(verticalShader, fragmentShader);
    free(verticalShader);
    free(fragmentShader);
    return result;
}

int FirstDrawer::onSizeChanged(int width, int height) {
    if (!glProgrem) {
        ALOGI("failed to create glprogram");
        return GL_FALSE;
    }
    mWidth = width;
    mHeight = height;
    ALOGI("onSizeChanged(%d,%d)", width, height);
    return GL_TRUE;
}

int FirstDrawer::draw() {
    if (!glProgrem) {
        return GL_FALSE;
    }
    GLfloat vVertexts[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(glProgrem);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertexts);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    eglSwapBuffers(eglDisplay, eglSurface);
    ALOGI("draw picture:");
    return GL_TRUE;
}

