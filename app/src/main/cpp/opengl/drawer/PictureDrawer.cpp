//
// Created by tom1 on 2020/9/7.
//

#include "PictureDrawer.h"

PictureDrawer::PictureDrawer(AAssetManager *manager,
                             const char *verticalPath, const char *fragmentPath,
                             const char *imagePath) : BaseRender(manager) {


}

int PictureDrawer::initSurface(JNIEnv *jniEnv, jobject surface) {
    return GL_TRUE;
}

int PictureDrawer::draw() {
    return GL_TRUE;
}
