//
// Created by tom1 on 2020/9/27.
//

#ifndef LEARNOPENGL_MODEL_H
#define LEARNOPENGL_MODEL_H

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/version.h"
#include "assimp/postprocess.h"

#include "ijksdl_log.h"

class Model {
private:
    void processNode(aiNode *node, aiScene *scene);

    void processMesh();

public:
    void loadModel( const char *modelPath);
};

#endif //LEARNOPENGL_MODEL_H
