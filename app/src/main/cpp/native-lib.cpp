#include <jni.h>
#include <string>
#include "opengl/WlOpengl.h"

WlOpengl *wlOpengl = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance, jobject surface) {
    // TODO
    if(wlOpengl == NULL)
    {
        wlOpengl = new WlOpengl();
    }
    wlOpengl->onCreateSurface(env, surface);

}


extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceChange(JNIEnv *env, jobject instance, jint width,
                                               jint height) {
    if(wlOpengl != NULL)
    {
        wlOpengl->onChangeSurface(width, height);
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_imgData(JNIEnv *env, jobject instance, jint width, jint height, jint length,
                                         jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);
    if(wlOpengl != NULL)
    {
        wlOpengl->setPilex(data, width, height, length);
    }
    env->ReleaseByteArrayElements(data_, data, 0);
}



extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceDestroy(JNIEnv *env, jobject instance) {

    if(wlOpengl != NULL)
    {
        wlOpengl->onDestorySurface();
        delete  wlOpengl;
        wlOpengl = NULL;
    }

}extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceChangeFilter(JNIEnv *env, jobject instance) {

    if(wlOpengl != NULL)
    {
        wlOpengl->onChangeFilter();
    }

}