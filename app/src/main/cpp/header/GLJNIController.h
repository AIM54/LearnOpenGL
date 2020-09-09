//
// Created by tom1 on 2020/9/9.
//

#ifndef LEARNOPENGL_GLJNICONTROLLER_H
#define LEARNOPENGL_GLJNICONTROLLER_H

#include <jni.h>

void onSurfaceCreated(JNIEnv
                      *env,
                      jobject thiz
);

void onSurfaceChanged(JNIEnv
                 *env,
                 jobject thiz,
                 jint
                 width,
                 jint height
);

void onDrawFrame(JNIEnv
                 *env,
                 jobject thiz
);

#endif //LEARNOPENGL_GLJNICONTROLLER_H
