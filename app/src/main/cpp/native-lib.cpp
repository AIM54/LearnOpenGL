#include <jni.h>
#include <string>
extern "C"{
#include "libavformat/avformat.h"
}

#include "assimp/version.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_bian_learnopengl_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = avformat_license() ;
    return env->NewStringUTF(hello.c_str());
}
