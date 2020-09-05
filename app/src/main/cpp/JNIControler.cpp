//
// Created by tom1 on 2020/9/1.
//
#include <jni.h>
#include <android/log.h>
#include <ijksdl_log.h>
#include "JNIControler.h"
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include "gl3stub.h"
#include "RenderFactory.h"
#define MY_OPENGL_RENDER  "com/bian/learnopengl/nativeutil/MyRender"

#define NELE(x) sizeof(x)/sizeof(x[0])

BaseRender *mCurrentRender;

static JNINativeMethod renderMethods[] = {
        {"init",          "(Landroid/content/res/AssetManager;)V", (void *) init},
        {"initSurface",   "(Landroid/view/Surface;)I",             (void *) initSurface},
        {"onSizeChanged", "(II)I",                                 (void *) onSizeChanged},
        {"draw",          "()I",                                   (void *) draw},
        {"pause",         "()I",                                   (void *) pause},
        {"resume",        "()I",                                   (void *) resume},
        {"destroyView",   "()I",                                   (void *) destroyView}
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
    ALOGE("renderMethods.length is :%d", NELE(renderMethods));
    jniEnv->RegisterNatives(renderClass, renderMethods, NELE(renderMethods));
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

void init(JNIEnv
          *env,
          jobject thiz, jobject
          assert) {
    AAssetManager *manager = AAssetManager_fromJava(env, assert);
    jclass renderClass = env->FindClass(MY_OPENGL_RENDER);;
    jint renderType = env->GetIntField(thiz, env->GetFieldID(renderClass, "renderType", "I"));
    ALOGI("the renderType is :%d", renderType);
    mCurrentRender = createRender(renderType, manager);
}

jint initSurface(JNIEnv
                 *env,
                 jobject thiz, jobject
                 surface) {
    if (gl3stubInit()!= GL_TRUE) {
        return GL_FALSE;
    }
    mCurrentRender->initSurface(env, surface);
    return GL_TRUE;
}

jint onSizeChanged(JNIEnv
                   *env,
                   jobject thiz, jint
                   width,
                   jint height
) {
    mCurrentRender->onSizeChanged(width, height);
    return 1;
}

jint draw(JNIEnv
          *env,
          jobject thiz
) {
    mCurrentRender->draw();
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

jint destroyView(JNIEnv
                 *env,
                 jobject thiz
) {
    mCurrentRender->destroyView();
    return 1;
}


