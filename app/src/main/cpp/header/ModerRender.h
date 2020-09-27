//
// Created by bian on 2020/9/23.
//

#ifndef LEARNOPENGL_MODERRENDER_H
#define LEARNOPENGL_MODERRENDER_H

#include "glm/glm.hpp"
#include "NewBaseRender.h"

class ModerRender : public NewBaseRender {
public:
    ModerRender(AAssetManager *manager);

    void loadModel( const char *modelPath);


protected:
    void onDraw(float deltaTime) override;

};


#endif //LEARNOPENGL_MODERRENDER_H
