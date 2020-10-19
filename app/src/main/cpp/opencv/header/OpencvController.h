//
// Created by bian on 2020/10/7.
//

#ifndef LEARNOPENGL_OPENCVCONTROLLER_H
#define LEARNOPENGL_OPENCVCONTROLLER_H

#include <jni.h>

class OpencvController {

};

void readImage(JNIEnv
               *env,
               jobject thiz, jstring
               imagePath);

void readVideo(JNIEnv
               *env,
               jobject thiz, jstring
               videoPath);


#endif //LEARNOPENGL_OPENCVCONTROLLER_H
