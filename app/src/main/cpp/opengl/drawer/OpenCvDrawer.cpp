//
// Created by tom1 on 2020/10/26.
//

#include <gl3stub.h>
#include "OpenCvDrawer.h"
#include "opencv2/opencv.hpp"
#include "ijksdl_log.h"

using namespace cv;

OpenCvDrawer::OpenCvDrawer(AAssetManager *manager,
                           const char *imagePath) : NewBaseRender(manager), mImagePath(nullptr),
                                                    verticalShader(nullptr),
                                                    fragmentShader(nullptr) {
    ALOGI("OpenCvDrawer::OpenCvDrawer(AAssetManager *manager,const char *imagePath)");
    mImagePath = static_cast<char *>(malloc((strlen(imagePath) + 1) * sizeof(char)));
    strcpy(mImagePath, imagePath);
    verticalShader = readStringFromAssert(manager, "shaders/FirstPicVerticalShader.glsl");
    fragmentShader = readStringFromAssert(manager, "shaders/FirstPicFragmentShader.glsl");
}

int OpenCvDrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    if (!BaseRender::initSurface(jniEnv, surface)) {
        return GL_FALSE;
    }
    Mat imgPic = imread(mImagePath);
    if (imgPic.empty() || !gl3stubInit()) {
        ALOGE("imgPic.empty()");
        GL_FALSE;
    }
    ALOGI("imgPic.cols:%d,imgPic.rows:%d", imgPic.cols, imgPic.rows);
    mProgram = esLoadProgram(verticalShader, fragmentShader);
    GLfloat verticals[] = {
            // 顶点                  颜色                    纹理
            -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
    };
    GLushort indics[] = {0, 1, 2, 2, 1, 3};
    glGenBuffers(2, mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indics), indics, GL_STATIC_DRAW);
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[1]);
    glEnableVertexAttribArray(VERTEX_POS_INDEX);
    glEnableVertexAttribArray(COLOR_POS_INDEX);
    glEnableVertexAttribArray(TEX_POS_INDEX);

    glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) 0);
    glVertexAttribPointer(COLOR_POS_INDEX, COLOR_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) (sizeof(GLfloat) * VERTEX_POS_SIZE));
    glVertexAttribPointer(TEX_POS_INDEX, TEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) (sizeof(GLfloat) * (VERTEX_POS_SIZE + COLOR_POS_SIZE)));
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgPic.cols, imgPic.rows, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 imgPic.ptr());
    glGenerateMipmap(GL_TEXTURE_2D);
    GLint texLocation = glGetUniformLocation(mProgram, "ourTexture");
    glUniform1i(texLocation, 0);
    glBindVertexArray(0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    return GL_TRUE;
}

void OpenCvDrawer::onDraw(float deltaTime) {
    glViewport(0, 0, getWidth(), getHeight());
    glUseProgram(mProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, (const void *) 0);
    glBindVertexArray(0);
    eglSwapBuffers(eglDisplay, eglSurface);
}

OpenCvDrawer::~OpenCvDrawer() {
    if (mImagePath) {
        free(mImagePath);
        mImagePath = nullptr;
    }
    if (verticalShader) {
        free(verticalShader);
        verticalShader = nullptr;
    }
    if (fragmentShader) {
        free(fragmentShader);
        fragmentShader = nullptr;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteProgram(mProgram);
    glDeleteBuffers(2, mVBO);
    glDeleteVertexArrays(1, &mVAO);
}