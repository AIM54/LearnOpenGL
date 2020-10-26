//
// Created by tom1 on 2020/10/26.
//

#ifndef LEARNOPENGL_OPENCVDRAWER_H
#define LEARNOPENGL_OPENCVDRAWER_H

#include "NewBaseRender.h"

class OpenCvDrawer : public NewBaseRender {
public:
    OpenCvDrawer(AAssetManager *manager,
                 const char *imagePath);

protected:
    void onDraw(float deltaTime) override;

};


#endif //LEARNOPENGL_OPENCVDRAWER_H
