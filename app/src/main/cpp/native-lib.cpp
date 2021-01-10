#include <jni.h>
#include <string>
#include "egl/WlEglHelper.h"
#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "egl/WlEglThread.h"


ANativeWindow *nativeWindow = NULL;
WlEglThread *wlEglThread = NULL;

void callback_SurfaceCrete(void *ctx)
{
    LOGD("callback_SurfaceCrete");
    WlEglThread *wlEglThread = static_cast<WlEglThread *>(ctx);
}

void callback_SurfacChange(int w, int h, void *ctx)
{
    LOGD("callback_SurfacChange");
    WlEglThread *wlEglThread = static_cast<WlEglThread *>(ctx);
    glViewport(0, 0, w, h);//设置窗口大小
}

void callback_SurfaceDraw(void *ctx)
{
    LOGD("callback_SurfaceDraw");
    WlEglThread *wlEglThread = static_cast<WlEglThread *>(ctx);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);//设置填充颜色
    glClear(GL_COLOR_BUFFER_BIT);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
    LOGE("Java_com_wyp_opengl_NativeOpengl_surfaceCreate 0");
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    wlEglThread = new WlEglThread();
    //设置渲染方式
    wlEglThread->setRenderType(OPENGL_RENDER_HANDLE);
    //设置回调函数
    wlEglThread->callBackOnCreate(callback_SurfaceCrete, wlEglThread);
    wlEglThread->callBackOnChange(callback_SurfacChange, wlEglThread);
    wlEglThread->callBackOnDraw(callback_SurfaceDraw, wlEglThread);

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