//
// Created by bian on 2020/9/3.
//

#ifndef LEARNOPENGL_FIRSTDRAWER_H
#define LEARNOPENGL_FIRSTDRAWER_H

#include "BaseDrawer.h"

class FirstDrawer : public BaseDrawer {

public:

    int onSizeChanged(int width, int height) override;

    int draw() override;

};


#endif //LEARNOPENGL_FIRSTDRAWER_H
