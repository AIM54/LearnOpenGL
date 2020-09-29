//
// Created by tom1 on 2020/9/29.
//

#ifndef LEARNOPENGL_VIDEORECORDERPREVIEWER_H
#define LEARNOPENGL_VIDEORECORDERPREVIEWER_H

#include "EGLContextHelper.h"
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

class VideoRecorderPreviewer {
public:
    void init(ANativeWindow *nativeWindow);

    GLuint *mTexture;
};


#endif //LEARNOPENGL_VIDEORECORDERPREVIEWER_H
