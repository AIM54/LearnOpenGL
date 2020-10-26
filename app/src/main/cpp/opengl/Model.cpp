//
// Created by tom1 on 2020/9/27.
//
#include "Model.h"

void Model::loadModel(const char *modelPath) {
    ALOGI("aiGetLegalString:%s", aiGetLegalString());
    Assimp::Importer importer;
    const aiScene *mRootScene = importer.ReadFile(modelPath,
                                                  aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!mRootScene || mRootScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !mRootScene->mRootNode) {
        ALOGI("failed to load model the reason is :%s", importer.GetErrorString());
        return;
    }
    processNode(mRootScene->mRootNode, const_cast<aiScene *>(mRootScene));
}

void Model::processNode(aiNode *node, aiScene *scene) {

}


