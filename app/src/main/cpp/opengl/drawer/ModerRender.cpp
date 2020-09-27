//
// Created by bian on 2020/9/23.
//

#include "ModerRender.h"
#include "Model.h"

ModerRender::ModerRender(AAssetManager *manager) : NewBaseRender(manager) {

}

void ModerRender::loadModel( const char *modelPath) {
    Model *model = new Model();
    model->loadModel(modelPath);
}

void ModerRender::onDraw(float deltaTime) {

}