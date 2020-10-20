//
// Created by tom1 on 2020/10/20.
//

#include "SphereDrawer.h"
#include <math.h>

SphereDrawer::SphereDrawer(AAssetManager *manager) : NewBaseRender(manager) {

}

void SphereDrawer::initData() {
    const int angleSpan = 10;
    double radius = 0.8;
    for (int vAngle = -90; vAngle < 90; vAngle += angleSpan) {
        for (int hAngle = 0; hAngle < 360; hAngle += angleSpan) {
            double x1 = radius * UNIT_SIZE * cos(to_radians(vAngle)) * cos(to_radians(hAngle));
            double y1 = radius * UNIT_SIZE * cos(to_radians(vAngle)) * sin(to_radians(hAngle));
            double z1 = radius * UNIT_SIZE * sin(to_radians(vAngle));


        }
    }
}
