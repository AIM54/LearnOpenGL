//
// Created by bian on 2020/9/6.
//

#include "gl3stub.h"
#include "VBODrawer.h"

#include "LogUtil.h"

#define  VERTEX_POS_INDEX 0
#define  VERTEX_POS_SIZE  3

#define  COLOR_POS_INDEX  1
#define  COLOR_POS_SIZE   4

#define  VERTEX_STRIDE (sizeof(GLfloat)*(VERTEX_POS_SIZE+COLOR_POS_SIZE))

VBODrawer::VBODrawer(AAssetManager *manager,
                     const char *verticalPath, const char *fragmentPath)
        : BaseRender(manager) {
    verticalShader = readStringFromAssert(manager, verticalPath);
    fragmentShader = readStringFromAssert(manager, fragmentPath);
}

int VBODrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    BaseRender::initSurface(jniEnv, surface);
    mProgram = esLoadProgram(verticalShader, fragmentShader);
    if (!mProgram) {
        return GL_FALSE;
    }
    //原来加上下面的这一行就可以了，差点被搞死
    if (!gl3stubInit()) {
        return GL_FALSE;
    }
    free(verticalShader);
    free(fragmentShader);
    verticalShader = nullptr;
    fragmentShader = nullptr;
    GLfloat verticals[4 * (VERTEX_POS_SIZE + COLOR_POS_SIZE)] = {
            -0.8f, 0.8f, 0.0f,        // v0
            1.0f, 1.0f, 0.0f, 1.0f,  // c0
            -0.8f, -0.8f, 0.0f,        // v1
            0.0f, 1.0f, 0.0f, 1.0f,  // c1
            0.8f, -0.8f, 0.0f,        // v2
            0.0f, 0.0f, 1.0f, 1.0f,  // c2
            0.8f, 0.8f, 0.0f,        // v3
            0.0f, 0.0f, 1.0f, 1.0f,  // c3
    };
    GLushort indics[6] = {0, 1, 2, 2, 0, 3};
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
    glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) 0);
    glVertexAttribPointer(COLOR_POS_INDEX, COLOR_POS_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
                          (const void *) (sizeof(GLfloat) * VERTEX_POS_SIZE));
    glBindVertexArray(0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    ALOGI("glClearColor");
    return GL_TRUE;
}

int VBODrawer::draw() {
    if (!mProgram) {
        return GL_FALSE;
    }
    glViewport(0, 0, getWidth(), getHeight());
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mProgram);
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, (const void *) 0);
    glBindVertexArray(0);
    eglSwapBuffers(eglDisplay, eglSurface);
    return GL_TRUE;
}

int VBODrawer::destroyView() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(2, mVBO);

}

