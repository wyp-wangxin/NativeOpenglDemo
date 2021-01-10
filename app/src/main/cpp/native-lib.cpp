#include <jni.h>
#include <string>
#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "android/native_window.h"


extern "C"
JNIEXPORT jstring

JNICALL
Java_com_wyp_nativeopengldemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
