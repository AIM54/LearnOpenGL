//
// Created by bian on 2020/9/3.
//

#ifndef LEARNOPENGL_FIRSTDRAWER_H
#define LEARNOPENGL_FIRSTDRAWER_H

#include "BaseRender.h"

class FirstDrawer : public BaseRender {

public:


    FirstDrawer(AAssetManager *manager);

    int onSizeChanged(int width, int height) override;

    int draw() override;

};


#endif //LEARNOPENGL_FIRSTDRAWER_H
