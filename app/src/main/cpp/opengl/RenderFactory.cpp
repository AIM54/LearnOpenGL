//
// Created by bian on 2020/9/3.
//

#include "BaseRender.h"
#include "RenderFactory.h"
#include "FirstDrawer.h"
#include "VBODrawer.h"
#include "PictureDrawer.h"
#include "OpenCvDrawer.h"
#include "ModerRender.h"

BaseRender *createRender(int type, AAssetManager *manager, const char *string) {
    BaseRender *baseDrawer = nullptr;
    if (type == OPENCV_RENDER_TYPE) {
        baseDrawer = new OpenCvDrawer(manager, string);
    } else if (type == OPENCV_MODEL_TYPE) {
        baseDrawer = new ModerRender(manager, string);
    } else if (string) {
        baseDrawer = new PictureDrawer(manager, string);
    } else {
        baseDrawer = new VBODrawer(manager, "shaders/VAOVerticalShader.glsl",
                                   "shaders/VAOFragmentShader.glsl");
    }
    return baseDrawer;
}
