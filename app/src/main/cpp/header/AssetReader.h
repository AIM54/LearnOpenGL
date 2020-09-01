//
// Created by tom1 on 2020/9/1.
//

#ifndef LEARNOPENGL_ASSETREADER_H
#define LEARNOPENGL_ASSETREADER_H

#include <android/asset_manager.h>
#include <GLES3/gl3.h>
#include <malloc.h>
#include <stdio.h>
#include "esUtil.h"

char *readStringFromAssert(AAssetManager *aAssetManager, char *path);


#endif //LEARNOPENGL_ASSETREADER_H
