//
// Created by bian on 2020/9/3.
//

#ifndef LEARNOPENGL_RENDERFACTORY_H
#define LEARNOPENGL_RENDERFACTORY_H

#include "BaseRender.h"
#include <android/asset_manager.h>

BaseRender *createRender(int type, AAssetManager *manager);

#endif //LEARNOPENGL_RENDERFACTORY_H
