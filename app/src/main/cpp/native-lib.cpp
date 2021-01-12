#include <jni.h>
#include <string>

#include "android/native_window.h"
#include "android/native_window_jni.h"
#include "egl/WlEglThread.h"
#include "shaderutil/WlShaderUtil.h"
#include "matrix/MatrixUtil.h"


const char *vertex = "attribute vec4 v_Position;\n"
        "attribute vec2 f_Position;\n"
        "varying vec2 ft_Position;\n"
        "uniform mat4 u_Matrix;\n"
        "void main() {\n"
        "    ft_Position = f_Position;\n"
        "    gl_Position = v_Position * u_Matrix;\n"
        "}";


const char *fragment = "precision mediump float;\n"
        "varying vec2 ft_Position;\n"
        "uniform sampler2D sTexture;\n"
        "void main() {\n"
        "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
        "}";

int program;
GLint vPosition;
GLint fPosition;
GLint sampler;
GLuint textureId;
GLint u_matrix;

int w;
int h;
void *pixels = NULL;


//定义定点坐标
float vertexs[] = {
        1,-1,
        1,1,
        -1,-1,
        -1,1
};

//设置纹理坐标
float fragments[] ={
        1,1,
        1,0,
        0,1,
        0,0
};
//定义矩阵
float matrix[16];

ANativeWindow *nativeWindow = NULL;
WlEglThread *wlEglThread = NULL;

void callback_SurfaceCrete(void *ctx)
{
    LOGD("callback_SurfaceCrete");
    WlEglThread *wlEglThread = static_cast<WlEglThread *>(ctx);

    program = createProgrm(vertex, fragment);
    LOGD("opengl program is %d", program);
    //vPosition = glGetAttribLocation(program, "a_position");//得到属性，给这个属性传值就行了

    vPosition = glGetAttribLocation(program, "v_Position");//顶点坐标
    fPosition = glGetAttribLocation(program, "f_Position");//纹理坐标
    sampler = glGetUniformLocation(program, "sTexture");//2D纹理
    u_matrix = glGetUniformLocation(program, "u_Matrix");

    initMatrix(matrix);
   // rotateMatrix(90,matrix);
   // scaleMatrix(0.5,matrix);//缩小为原来的二分之一
    transMatrix(0.5,0,matrix);//理解：0.5 即是在x轴向右移动了四分一的位置，因为坐标系是归一画的，0.5刚好就是1/4

    glGenTextures(1, &textureId);//2.1、创建纹理：

    glBindTexture(GL_TEXTURE_2D, textureId);//2.2、绑定纹理：
    //设置环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    if(pixels != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
    glBindTexture(GL_TEXTURE_2D, 0);//解绑

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
    glUniformMatrix4fv(u_matrix, 1,//表示只传递一个矩阵过来
                       GL_FALSE, matrix);
   /* glEnableVertexAttribArray(vPosition);//让定点的数据可用
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
   /* glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    LOGD("callback_SurfaceDraw 2222");*/

    glActiveTexture(GL_TEXTURE5);
    glUniform1i(sampler, 5);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);

    glEnableVertexAttribArray(fPosition);
    glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
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
}extern "C"
JNIEXPORT void JNICALL
Java_com_wyp_opengl_NativeOpengl_imgData(JNIEnv *env, jobject instance, jint width, jint height, jint length,
                                         jbyteArray data_) {
    jbyte *data = env->GetByteArrayElements(data_, NULL);

    w = width;
    h = height;
    pixels = malloc(length);
    memcpy(pixels, data, length);

    env->ReleaseByteArrayElements(data_, data, 0);
}