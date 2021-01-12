//
// Created by yangw on 2019-3-31.
//

#ifndef NATIVEOPENGLDEMO_WLOPENGL_H
#define NATIVEOPENGLDEMO_WLOPENGL_H

#include "../egl/WlEglThread.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "WlBaseOpengl.h"
#include "WlFilterOne.h"

class WlOpengl {

public:
    WlEglThread *wlEglThread = NULL;
    ANativeWindow *nativeWindow = NULL;
    WlBaseOpengl *baseOpengl = NULL;

    int pic_width;
    int pic_height;
    void *pilex = NULL;

public:
    WlOpengl();
    ~WlOpengl();

    void onCreateSurface(JNIEnv *env, jobject surface);

    void onChangeSurface(int width, int height);

    void onDestorySurface();

    void setPilex(void *data, int width, int height, int length);

};


#endif //NATIVEOPENGLDEMO_WLOPENGL_H
