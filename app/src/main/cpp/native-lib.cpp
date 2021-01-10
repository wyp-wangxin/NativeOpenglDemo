#include <jni.h>
#include <string>
#include "egl/WlEglHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "egl/WlEglThread.h"


ANativeWindow *nativeWindow = NULL;
WlEglThread *wlEglThread = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    LOGE("Java_com_wyp_opengl_NativeOpengl_surfaceCreate 0");
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    wlEglThread = new WlEglThread();
    wlEglThread->onSurfaceCreate(nativeWindow);

}


extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance, jint width,
                                               jint height) {

    // TODO
    if(wlEglThread != NULL)
    {
        wlEglThread->onSurfaceChange(width, height);
    }
}