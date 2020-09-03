//
// Created by tom1 on 2020/9/3.
//

#ifndef LEARNOPENGL_JNICONTROLER_H
#define LEARNOPENGL_JNICONTROLER_H

#include <jni.h>
jint init(JNIEnv
          *env,
          jobject thiz, jobject
          surface);

jint onSizeChanged(JNIEnv
                   *env,
                   jobject thiz, jint
                   width,
                   jint height
);

jint draw(JNIEnv
          *env,
          jobject thiz
);

jint pause(JNIEnv
           *env,
           jobject thiz
);

jint resume(JNIEnv
            *env,
            jobject thiz
);

jint destroy(JNIEnv
             *env,
             jobject thiz
);
#endif //LEARNOPENGL_JNICONTROLER_H

