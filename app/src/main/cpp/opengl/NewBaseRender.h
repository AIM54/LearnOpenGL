//
// Created by bian on 2020/9/23.
//

#ifndef LEARNOPENGL_NEWBASERENDER_H
#define LEARNOPENGL_NEWBASERENDER_H

#include "BaseRender.h"

class NewBaseRender : public BaseRender {
private:
    float mLastTime;
public:
    int draw() override;

    NewBaseRender(AAssetManager *manager);

protected:
    virtual void onDraw(float deltaTime) = 0;

};


#endif //LEARNOPENGL_NEWBASERENDER_H
