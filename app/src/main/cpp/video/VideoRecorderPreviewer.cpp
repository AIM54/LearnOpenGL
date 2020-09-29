//
// Created by tom1 on 2020/9/29.
//

#include "VideoRecorderPreviewer.h"

void VideoRecorderPreviewer::init(ANativeWindow *nativeWindow) {
    if (!gl3stubInit()) {
        return;
    }
    glGenTextures(1, mTexture);

}
