//
// Created by wyp on 2021/1/10.
//

#ifndef NATIVEOPENGLDEMO_WLEGLTHREAD_H
#define NATIVEOPENGLDEMO_WLEGLTHREAD_H
#include <EGL/eglplatform.h>
#include "pthread.h"
#include "android/native_window.h"
#include "WlEglHelper.h"
#include <unistd.h>
#include "GLES2/gl2.h"


class WlEglThread {
public:

    pthread_t eglThread = -1;
    ANativeWindow *nativeWindow = NULL;

    bool isCreate = false;
    bool isChange = false;
    bool isExit = false;
    bool isStart = false;

    bool surfaceWidth = 0;
    bool surfaceHeight = 0;


public:
    WlEglThread();
    ~WlEglThread();

    void onSurfaceCreate(EGLNativeWindowType window);

    void onSurfaceChange(int width, int height);


};


#endif //NATIVEOPENGLDEMO_WLEGLTHREAD_H
