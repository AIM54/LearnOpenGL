//
// Created by bian on 2020/9/5.
//

#include "FirstDrawer.h"

FirstDrawer::FirstDrawer(AAssetManager *manager) : BaseRender(manager) {

}

int FirstDrawer::draw() {
    return GL_TRUE;
}

int FirstDrawer::onSizeChanged(int width, int height) {
    return GL_TRUE;
}