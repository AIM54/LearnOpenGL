//
// Created by tom1 on 2020/9/1.
//
#include <jni.h>
#include <android/log.h>
#include <ijksdl_log.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <MemoryTrace.hpp>
#include "gl3stub.h"
#include "RenderFactory.h"
#include "JNIControler.h"
#include "BaseOfflineRender.h"
#include "FirstOffline.h"

extern "C" {
#include "libavformat/avformat.h"
}

#include "version.h"
#include "leaktracer.h"

#define MY_OPENGL_RENDER  "com/bian/learnopengl/nativeutil/MyRender"


#define NELE(x) sizeof(x)/sizeof(x[0])

BaseRender *mCurrentRender;
static JNINativeMethod renderMethods[] = {
        {"init",          "(Landroid/content/res/AssetManager;Ljava/lang/String;)V", (void *) init},
        {"initSurface",   "(Landroid/view/Surface;)I",                               (void *) initSurface},
        {"onSizeChanged", "(II)I",                                                   (void *) onSizeChanged},
        {"draw",          "()I",                                                     (void *) draw},
        {"drawOffScreen", "(Landroid/content/res/AssetManager;)V",                   (void *) drawOffScreen},
        {"pause",         "()I",                                                     (void *) pause},
        {"resume",        "()I",                                                     (void *) resume},
        {"destroyView",   "()I",                                                     (void *) destroyView}
};


void onImageDataCallback(Byte *imageData) {

}

void drawOffScreen(JNIEnv *env,
                   jobject thiz, jobject assert) {
    AAssetManager *manager = AAssetManager_fromJava(env, assert);
    BaseOfflineRender *baseOffScreenDrawer = new FirstOffline(manager);
    baseOffScreenDrawer->setImageCallBack(onImageDataCallback);
    baseOffScreenDrawer->draw();
    baseOffScreenDrawer->onDestroy();
    delete baseOffScreenDrawer;
}


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
    leaktracer::MemoryTrace::GetInstance().startMonitoringAllThreads();
    jniEnv->RegisterNatives(renderClass, renderMethods, NELE(renderMethods));
    jniEnv->DeleteLocalRef(renderClass);
    return JNI_VERSION_1_6;
};

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    if (mCurrentRender) {
        delete mCurrentRender;
        mCurrentRender = nullptr;
    }
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
    leaktracer::MemoryTrace::GetInstance().writeLeaksToFile("/mnt/sdcard/mem_leak.log");
    jniEnv->UnregisterNatives(renderClass);

};

void init(JNIEnv
          *env,
          jobject thiz, jobject
          assert, jstring imagePath) {
    AAssetManager *manager = AAssetManager_fromJava(env, assert);
    jclass renderClass = env->FindClass(MY_OPENGL_RENDER);;
    jint renderType = env->GetIntField(thiz, env->GetFieldID(renderClass, "renderType", "I"));
    ALOGI("the renderType is :%d", renderType);
    if (mCurrentRender) {
        delete mCurrentRender;
        mCurrentRender = nullptr;
    }
    ALOGI("avformat_license:%s", avformat_license());
    ALOGI("aiGetLegalString:%s", aiGetLegalString());
    if (imagePath) {
        const char *imageUrl = env->GetStringUTFChars(imagePath, 0);
        mCurrentRender = createRender(renderType, manager, imageUrl);
        env->ReleaseStringUTFChars(imagePath, imageUrl);
    } else {
        mCurrentRender = createRender(renderType, manager, nullptr);
    }
}

jint initSurface(JNIEnv
                 *env,
                 jobject thiz, jobject
                 surface) {
    if (gl3stubInit() != GL_TRUE) {
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
    if (mCurrentRender) {
        mCurrentRender->onSizeChanged(width, height);
    }
    return 1;
}

jint draw(JNIEnv
          *env,
          jobject thiz
) {
    if (mCurrentRender) {
        mCurrentRender->draw();
    }
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
    if (mCurrentRender) {
        mCurrentRender->destroyView();
    }
    return 1;
}




