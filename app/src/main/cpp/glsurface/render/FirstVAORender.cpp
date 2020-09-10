//
// Created by tom1 on 2020/9/10.
//

#include "gl3stub.h"
#include "FirstVAORender.h"
#include "esUtil.h"
#include "ijksdl_log.h"

#define  VERTEX_POS_INDEX 0
#define  VERTEX_POS_SIZE  3

#define  COLOR_POS_INDEX  1
#define  COLOR_POS_SIZE   4

#define  VERTEX_STRIDE (sizeof(GLfloat)*(VERTEX_POS_SIZE+COLOR_POS_SIZE))

void FirstVAORender::init(const char *vertical, const char *fragment) {
    if (!gl3stubInit()) {
        return;
    }
    mProgram = esLoadProgram(vertical, fragment);
    if (!mProgram) {
        return;
    }
    GLfloat verticals[3 * (VERTEX_POS_SIZE + COLOR_POS_SIZE)] = {
            0.0f, 0.5f, 0.0f,        // v0
            1.0f, 0.0f, 0.0f, 1.0f,  // c0
            -0.5f, -0.5f, 0.0f,        // v1
            0.0f, 1.0f, 0.0f, 1.0f,  // c1
            0.5f, -0.5f, 0.0f,        // v2
            0.0f, 0.0f, 1.0f, 1.0f,  // c2
    };
    GLushort indics[3] = {0, 1, 2};
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
    glVertexAttribPointer(COLOR_POS_INDEX, COLOR_POS_SIZE, GL_FLOAT, GL_FALSE,
                          VERTEX_STRIDE, (const void *) (sizeof(GLfloat) * VERTEX_POS_SIZE));
    glBindVertexArray(0);

    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
}

void FirstVAORender::onSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void FirstVAORender::onDraw() {
    if (!mProgram) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mProgram);
    glBindVertexArray(mVAO);
    glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, ( const void * ) 0 );
    glBindVertexArray(0);
    ALOGI("onDraw");
}

FirstVAORender::~FirstVAORender() {
    if (mProgram) {
        glDeleteProgram(mProgram);
    }
    if (mVBO) {
        glDeleteBuffers(2, mVBO);
    }
    if (mVAO){
        glDeleteVertexArrays(1,&mVAO);
    }
}
