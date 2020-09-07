//
// Created by bian on 2020/9/6.
//

#include "VBODrawer.h"
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

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
    free(verticalShader);
    free(fragmentShader);
    verticalShader = nullptr;
    fragmentShader = nullptr;
    GLfloat verticals[3 * (VERTEX_POS_SIZE + COLOR_POS_SIZE)] = {
            0.0f, 0.5f, 0.0f,        // v0
            1.0f, 0.0f, 0.0f, 1.0f,  // c0
            -0.5f, -0.5f, 0.0f,        // v1
            0.0f, 1.0f, 0.0f, 1.0f,  // c1
            0.5f, -0.5f, 0.0f,        // v2
            0.0f, 0.0f, 1.0f, 1.0f,  // c2
    };
    GLushort indics[3] = {0, 1, 2};
    glGenBuffers(2, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticals), verticals, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indics), indics, GL_STATIC_DRAW);
    ALOGI("before genVAO");
    glGenVertexArrays(1, &vao);
    ALOGI("after genVAO");
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, ebo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
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
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (const void *) 0);
    glBindVertexArray(0);
    return GL_TRUE;
}

