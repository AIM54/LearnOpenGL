//
// Created by tom1 on 2020/9/10.
//

#include "gl3stub.h"
#include "FirstVAORender.h"
#include "esUtil.h"

#define  VERTEX_POS_INDEX 0
#define  VERTEX_POS_SIZE  3

#define  COLOR_POS_INDEX  1
#define  COLOR_POS_SIZE   4

#define  VERTEX_STRIDE (sizeof(GLfloat)*(VERTEX_POS_SIZE+COLOR_POS_SIZE))

void FirstVAORender::init(const char *vertical, const char *fragment) {
}

void FirstVAORender::onSizeChanged(int width, int height) {
}

void FirstVAORender::onDraw() {
}

FirstVAORender::~FirstVAORender() {
}
