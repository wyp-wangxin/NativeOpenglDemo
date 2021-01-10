//
// Created by wyp on 2021/1/10.
//

#include "WlEglThread.h"

WlEglThread::WlEglThread() {
    pthread_mutex_init(&pthread_mutex, NULL);
    pthread_cond_init(&pthread_cond, NULL);
}

WlEglThread::~WlEglThread() {
    pthread_mutex_destroy(&pthread_mutex);
    pthread_cond_destroy(&pthread_cond);
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
                wlEglThread->onCreate(wlEglThread->onCreteCtx);
            }

            if(wlEglThread->isChange)
            {
                LOGD("eglthread call surfaceChange");
                wlEglThread->isChange = false;
                //glViewport(0, 0, wlEglThread->surfaceWidth, wlEglThread->surfaceHeight);//设置窗口大小
                wlEglThread->onChange(wlEglThread->surfaceWidth, wlEglThread->surfaceHeight, wlEglThread->onChangeCtx);
                wlEglThread->isStart = true;
            }

            //
            LOGD("draw");
            if(wlEglThread->isStart)
            {
                //glClearColor(0.0f, 1.0f, 1.0f, 1.0f);//设置填充颜色
                //glClear(GL_COLOR_BUFFER_BIT);
                wlEglThread->onDraw(wlEglThread->onDrawCtx);
                wlEglHelper->swapBuffers();
            }

            if(wlEglThread->renderType == OPENGL_RENDER_AUTO)
            {
                usleep(1000000 / 60);
            }
            else
            {
                pthread_mutex_lock(&wlEglThread->pthread_mutex);
                pthread_cond_wait(&wlEglThread->pthread_cond, &wlEglThread->pthread_mutex);//会先解锁
                pthread_mutex_unlock(&wlEglThread->pthread_mutex);
            }

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

    if(eglThread == -1)
    {
        isCreate = true;
        nativeWindow = window;
        pthread_create(&eglThread, NULL, eglThreadImpl, this);
    }
}

void WlEglThread::onSurfaceChange(int width, int height) {

    isChange = true;
    surfaceWidth = width;
    surfaceHeight = height;
}
void WlEglThread::callBackOnCreate(WlEglThread::OnCreate onCreate, void *ctx) {
    this->onCreate = onCreate;
    this->onCreteCtx = ctx;
}

void WlEglThread::callBackOnChange(OnChange onChange, void *ctx) {
    this->onChange = onChange;
    this->onChangeCtx = ctx;
}

void WlEglThread::callBackOnDraw(OnDraw onDraw, void *ctx) {
    this->onDraw = onDraw;
    this->onDrawCtx = ctx;
}

void WlEglThread::setRenderType(int renderType) {
    this->renderType = renderType;
}

void WlEglThread::notifyRender() {
    pthread_mutex_lock(&pthread_mutex);
    pthread_cond_signal(&pthread_cond);
    pthread_mutex_unlock(&pthread_mutex);
}
