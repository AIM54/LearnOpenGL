//
// Created by tom1 on 2020/9/21.
//

#ifndef LEARNOPENGL_FIRSTOFFLINE_H
#define LEARNOPENGL_FIRSTOFFLINE_H

#include "BaseOfflineRender.h"

class FirstOffline : public BaseOfflineRender {
public:
    FirstOffline(AAssetManager *manager);

    virtual ~FirstOffline();

protected:

    char *verticalShader;
    char *fragmentShader;
    GLuint glProgrem;

    void initProgram() override;

    void onDraw() override;
};


#endif //LEARNOPENGL_FIRSTOFFLINE_H
