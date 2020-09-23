//
// Created by tom1 on 2020/9/21.
//

#include "FirstOffline.h"

extern "C" {
#include "AssetReader.h"
}

#include "ijksdl_log.h"

FirstOffline::FirstOffline(AAssetManager *manager) : BaseOfflineRender(manager) {
    if (eglContext == EGL_NO_CONTEXT) {
        return;
    }
    verticalShader = readStringFromAssert(manager, "shaders/FirstVerticalShader.glsl");
    fragmentShader = readStringFromAssert(manager, "shaders/FirstFragmentShader.glsl");
    initProgram();
}

void FirstOffline::initProgram() {
    glProgrem = esLoadProgram(verticalShader, fragmentShader);
    free(verticalShader);
    free(fragmentShader);
}

void FirstOffline::onDraw() {
    if (!glProgrem) {
        return;
    }
    GLfloat vVertexts[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
    glUseProgram(glProgrem);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertexts);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    Byte *imageData = new Byte[width * height * 4 * sizeof(Byte)];
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    if (PixCallBack) {
        PixCallBack(imageData);
    }
    delete[]imageData;
}

FirstOffline::~FirstOffline() {
    if (glProgrem) {
        glDeleteProgram(glProgrem);
    }
}