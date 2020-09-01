#include <jni.h>
#include <string>
#include "assimp/version.h"


extern "C" JNIEXPORT jstring JNICALL
Java_com_bian_learnopengl_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello =aiGetLegalString();
    return env->NewStringUTF(hello.c_str());
}
