//
// Created by bian on 2020/9/3.
//

#include "BaseRender.h"
#include "RenderFactory.h"
#include "FirstDrawer.h"
#include "VBODrawer.h"

BaseRender *createRender(int type, AAssetManager *manager) {
    BaseRender *baseDrawer = new VBODrawer(manager,"VAOVerticalShader.glsl","VAOFragmentShader.glsl");
    return baseDrawer;
}
