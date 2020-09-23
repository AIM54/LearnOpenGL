//
// Created by bian on 2020/9/23.
//

#include "NewBaseRender.h"

NewBaseRender::NewBaseRender(AAssetManager *manager) : BaseRender(manager) {
    mLastTime = GetCurrentTime();
}

int NewBaseRender::draw() {
    float nowTime = GetCurrentTime();
    onDraw(nowTime - mLastTime);
    mLastTime=nowTime;
    return GL_TRUE;
}
