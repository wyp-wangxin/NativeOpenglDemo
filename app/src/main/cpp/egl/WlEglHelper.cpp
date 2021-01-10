//
// Created by wyp on 2021/1/9.
//

#include "WlEglHelper.h"

WlEglHelper::WlEglHelper() {
    mEglDisplay = EGL_NO_DISPLAY;
    mEglSurface = EGL_NO_SURFACE;
    mEglContext = EGL_NO_CONTEXT;
    mEglConfig = NULL;
}

WlEglHelper::~WlEglHelper() {

}

int WlEglHelper::initEgl(EGLNativeWindowType window) {
    //1、得到默认的显示设备（就是窗口）
    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(mEglDisplay == EGL_NO_DISPLAY)
    {
        LOGE("eglGetDisplay error");
        return -1;
    }
    //2、初始化默认显示设备
    EGLint *version = new EGLint[2];
    if(!eglInitialize(mEglDisplay, &version[0], &version[1]))
    {
        LOGE("eglInitialize error");
        return -1;
    }

    //3、设置显示设备的属性
   /* const EGLint attribs[] = {
            EGL_RED_SIZE, 8,   //颜色
            EGL_GREEN_SIZE, 8, //颜色
            EGL_BLUE_SIZE, 8, //颜色
            EGL_ALPHA_SIZE, 8, //ALPHA
            EGL_DEPTH_SIZE, 8, //深度
            EGL_STENCIL_SIZE, 8, //模板
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,//版本
            EGL_NONE  //表示结尾
    };


    EGLint num_config;
    int res = eglChooseConfig(mEglDisplay,
                              attribs,
                              NULL, //查询用的configs
                              1, //返回一个恰当的 config
                              &num_config);
    if(!res)
    {
        LOGE("eglChooseConfig  error 1");
        return -1;
    }*/
    const EGLint attribs[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };

    EGLint num_config;
    if(!eglChooseConfig(mEglDisplay, attribs, NULL, 1, &num_config))
    {
        LOGE("eglChooseConfig  error 1");
        return -1;
    }

    //4、从系统中获取对应属性的配置
    if(!eglChooseConfig(mEglDisplay, attribs, &mEglConfig, num_config, &num_config))
    {
        LOGE("eglChooseConfig  error 2");
        return -1;
    }

    //5、创建EglContext
   /* int attrib_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };
    mEglContext = eglCreateContext(mEglDisplay,
                                   mEglConfig,
                                   EGL_NO_CONTEXT, //共享的EglContext，这里没有.
                                   attrib_list //版本信息
    );*/

    int attrib_list[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };

    mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, attrib_list);
    if(mEglContext == EGL_NO_CONTEXT)
    {
        LOGE("eglCreateContext  error");
        return -1;
    }
    //6、创建渲染的Surface
    /*mEglSurface = eglCreateWindowSurface(mEglDisplay,
                                         mEglConfig,
                                         window,
                                         NULL//属性传空就好
    );*/
    mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, window, NULL);
    if(mEglSurface == EGL_NO_SURFACE)
    {
        LOGE("eglCreateWindowSurface  error");
        return -1;
    }

    //7、
    if(!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext))
    {
        LOGE("eglMakeCurrent  error");
        return -1;
    }
    LOGD("egl init success! ");
    return 0;
}

//8、刷新数据，显示渲染场景
int WlEglHelper::swapBuffers() {
    if(mEglDisplay != EGL_NO_DISPLAY && mEglSurface != EGL_NO_SURFACE)
    {
        if(eglSwapBuffers(mEglDisplay, mEglSurface))
        {
            return 0;//成功返回0
        }
    }
    return -1;//失败返回-1

}

void WlEglHelper::destoryEgl() {
    if(mEglDisplay != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);//解绑
    }
    if(mEglDisplay != EGL_NO_DISPLAY && mEglSurface != EGL_NO_SURFACE)
    {
        eglDestroySurface(mEglDisplay, mEglSurface);
        mEglSurface = EGL_NO_SURFACE;
    }
    if(mEglDisplay != EGL_NO_DISPLAY && mEglContext != EGL_NO_CONTEXT){
        eglDestroyContext(mEglDisplay, mEglContext);
        mEglContext = EGL_NO_CONTEXT;
    }
    if(mEglDisplay != EGL_NO_DISPLAY)
    {
        eglTerminate(mEglDisplay);
        mEglDisplay = EGL_NO_DISPLAY;
    }
}
