//
// Created by tom1 on 2020/9/1.
//
#include <jni.h>
#include <android/log.h>
#include <ijksdl_log.h>
#include "JNIControler.h"

extern "C" {
#include "gl3stub.h"
}
#define MY_OPENGL_RENDER  "com/bian/learnopengl/nativeutil/MyRender"

static JNINativeMethod renderMethods[] = {
        {"init",          "(Landroid/view/Surface;)I", (void *) init},
        {"onSizeChanged", "(II)I",                     (void *) onSizeChanged},
        {"draw",          "()I",                       (void *) draw},
        {"pause",         "()I",                       (void *) pause},
        {"resume",        "()I",                       (void *) resume},
        {"destroy",       "()I",                       (void *) destroy}
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *jniEnv = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    ALOGE("className is :%s", MY_OPENGL_RENDER);
    jclass renderClass = jniEnv->FindClass(MY_OPENGL_RENDER);
    if (!renderClass) {
        ALOGE("failed to find class:%s", MY_OPENGL_RENDER);
        return JNI_ERR;
    }
    jniEnv->RegisterNatives(renderClass, renderMethods, 6);
    jniEnv->DeleteLocalRef(renderClass);
    return JNI_VERSION_1_6;
};

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    JNIEnv *jniEnv = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        ALOGE("failed to get env");
        return;
    }
    jclass renderClass = jniEnv->FindClass(MY_OPENGL_RENDER);
    if (!renderClass) {
        ALOGE("failed to find class:%s", MY_OPENGL_RENDER);
        return;
    }
    jniEnv->UnregisterNatives(renderClass);

};


jint init(JNIEnv
          *env,
          jobject thiz, jobject
          surface) {
    gl3stubInit();
    return 1;
}

jint onSizeChanged(JNIEnv
                   *env,
                   jobject thiz, jint
                   width,
                   jint height
) {
    return 1;
}

jint draw(JNIEnv
          *env,
          jobject thiz
) {
    return 1;
}

jint pause(JNIEnv
           *env,
           jobject thiz
) {
    return 1;
}

jint resume(JNIEnv
            *env,
            jobject thiz
) {
    return 1;
}

jint destroy(JNIEnv
             *env,
             jobject thiz
) {
    return 1;
}


