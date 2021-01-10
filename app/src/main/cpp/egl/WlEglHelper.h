//
// Created by wyp on 2021/1/9.
//

#ifndef NATIVEOPENGLDEMO_WLEGLHELPER_H
#define NATIVEOPENGLDEMO_WLEGLHELPER_H


#include <EGL/egl.h>
#include "../log/WlAndroidLog.h"
class WlEglHelper {
public:
    EGLDisplay  mEglDisplay;
    EGLSurface  mEglSurface;
    EGLConfig  mEglConfig;
    EGLContext mEglContext;

public:
    WlEglHelper();
    ~WlEglHelper();

    int initEgl(EGLNativeWindowType window);

    int swapBuffers();

    void destoryEgl();

};


#endif //NATIVEOPENGLDEMO_WLEGLHELPER_H
