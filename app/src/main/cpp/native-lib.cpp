#include <jni.h>
#include <string>

#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "egl/WlEglThread.h"
#include "shaderutil/WlShaderUtil.h"


const char *vertex = "attribute vec4 a_position;\n"
        "\n"
        "void main(){\n"
        "    gl_Position = a_position;\n"
        "}";
const char *fragment = "precision mediump float;\n"
        "\n"
        "void main(){\n"
        "    gl_FragColor = vec4(1f,0f,0f,1f);\n"
        "}";

int program;
GLint vPosition;
//定义定点坐标
float vertexs[] = {
       -1,-1,
        1,-1,
        -1,1,

       -1,1,
       1,-1,
       1,1
};



ANativeWindow *nativeWindow = NULL;
WlEglThread *wlEglThread = NULL;

void callback_SurfaceCrete(void *ctx)
{
    LOGD("callback_SurfaceCrete");
    WlEglThread *wlEglThread = static_cast<WlEglThread *>(ctx);

    program = createProgrm(vertex, fragment);
    LOGD("opengl program is %d", program);
    vPosition = glGetAttribLocation(program, "a_position");//得到属性，给这个属性传值就行了

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//设置填充颜色
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glEnableVertexAttribArray(vPosition);//让定点的数据可用
   /* glVertexAttribPointer(vPosition,
                          2,//一个点是由是x,y两个FLOAT表示的
                          GL_FLOAT,//类型
                          false,//不用归一化，因为我们的坐标本身就是归一化的
                          8,//跨度，一个点占用8个字节
                          vertexs
    );
    glDrawArrays(GL_TRIANGLES, //绘制三角形
                 0, //vertexs 从0下标开始
                 3//vertexs 长度是3
    );*/
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    LOGD("callback_SurfaceDraw 2222");

}

extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_surfaceCreate(JNIEnv *env, jobject instance, jobject surface) {

    // TODO
   // LOGE("Java_com_wyp_opengl_NativeOpengl_surfaceCreate 0");
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

        usleep(1000000);
        wlEglThread->notifyRender();
    }
}