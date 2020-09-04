//
// Created by bian on 2020/9/3.
//

#include "RenderFactory.h"
#include "FirstDrawer.h"

BaseDrawer *createRender(int type, AAssetManager *manager) {
    BaseDrawer *baseDrawer = new FirstDrawer();
    return baseDrawer;
}
