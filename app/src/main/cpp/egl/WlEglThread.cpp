//
// Created by wyp on 2021/1/10.
//

#include "WlEglThread.h"

WlEglThread::WlEglThread() {

}

WlEglThread::~WlEglThread() {

}


void * eglThreadImpl(void *context)
{
    WlEglThread *wlEglThread =(WlEglThread *)(context);

    if(wlEglThread != NULL)
    {
        WlEglHelper *wlEglHelper = new WlEglHelper();
        wlEglHelper->initEgl((wlEglThread->nativeWindow));

        wlEglThread->isExit = false;
        while(true)
        {
            if(wlEglThread->isCreate)
            {
                LOGD("eglthread call surfaceCreate");
                wlEglThread->isCreate = false;
            }

            if(wlEglThread->isChange)
            {
                LOGD("eglthread call surfaceChange");
                wlEglThread->isChange = false;
                glViewport(0, 0, wlEglThread->surfaceWidth, wlEglThread->surfaceHeight);//设置窗口大小
                wlEglThread->isStart = true;
            }

            //
            LOGD("draw");
            if(wlEglThread->isStart)
            {
                glClearColor(0.0f, 1.0f, 1.0f, 1.0f);//设置填充颜色
                glClear(GL_COLOR_BUFFER_BIT);
                wlEglHelper->swapBuffers();
            }
            usleep(1000000 / 60);
            if(wlEglThread->isExit)
            {
                break;
            }
        }
    }

//    pthread_exit(&wlEglThread->eglThread);
    return 0;
}


void WlEglThread::onSurfaceCreate(EGLNativeWindowType window) {
    nativeWindow = window;
    WlEglHelper *wlEglHelper = new WlEglHelper();
    wlEglHelper->initEgl(nativeWindow);
    glViewport(0, 0, 720, 1280);//设置窗口大小
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);//设置填充颜色
    glClear(GL_COLOR_BUFFER_BIT);
    wlEglHelper->swapBuffers();

  /*  if(eglThread == -1)
    {
        isCreate = true;
        nativeWindow = window;
        pthread_create(&eglThread, NULL, eglThreadImpl, this);
    }*/
}

void WlEglThread::onSurfaceChange(int width, int height) {

    isChange = true;
    surfaceWidth = width;
    surfaceHeight = height;
}
