//
// Created by tom1 on 2020/10/20.
//

#ifndef LEARNOPENGL_SPHEREDRAWER_H
#define LEARNOPENGL_SPHEREDRAWER_H

#include "NewBaseRender.h"
#include <vector>

class SphereDrawer : NewBaseRender {
private:
    std::vector<double > data;

    void initData();

public:
    SphereDrawer(AAssetManager *manager);

};
#define UNIT_SIZE 1
inline double to_radians(double digree) {
    return M_PI * (digree / 180.0);
}

#endif //LEARNOPENGL_SPHEREDRAWER_H
