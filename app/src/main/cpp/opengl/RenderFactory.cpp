//
// Created by bian on 2020/9/3.
//

#include <BaseRender.h>
#include "RenderFactory.h"
#include "FirstDrawer.h"

BaseRender *createRender(int type, AAssetManager *manager) {
    BaseRender *baseDrawer = new FirstDrawer(manager);
    return baseDrawer;
}
