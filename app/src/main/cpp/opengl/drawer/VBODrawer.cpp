//
// Created by bian on 2020/9/6.
//

#include "VBODrawer.h"
#include "libavformat/avformat.h"

VBODrawer::VBODrawer(AAssetManager *manager,
                     const char *verticalPath, const char *fragmentPath)
        : BaseRender(manager) {
    verticalShader = readStringFromAssert(manager, verticalPath);
    fragmentShader = readStringFromAssert(manager, fragmentPath);
}

int VBODrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    BaseRender::initSurface(jniEnv, surface);
    mProgram = esLoadProgram(verticalShader, fragmentShader);
    glGenVertexArrays(1, &vao);
    return GL_TRUE;
}

int VBODrawer::draw() {
    glViewport(0, 0, getWidth(), getHeight());

    return GL_TRUE;
}

