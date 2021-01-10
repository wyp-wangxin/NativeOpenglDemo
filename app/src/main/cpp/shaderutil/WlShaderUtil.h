//
// Created by wyp on 2021/1/10.
//

#ifndef NATIVEOPENGLDEMO_WLSHADERUTIL_H
#define NATIVEOPENGLDEMO_WLSHADERUTIL_H
#include <GLES2/gl2.h>

static int loadShaders(int shaderType, const char *code)
{
   /* //1、创建shader（着色器：顶点或片元）
    int shader = glCreateShader(shaderType);
    //2、加载shader源码并编译shader
    glShaderSource(shader,
                   1,//表示只有一个shader
                   &code, //代码
                   0//代表长度，为0 就会把code里面的所有内容全部加载
    );
    //并编译shader
    glCompileShader(shader);
    return  shader;*/
    int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);
    return  shader;
}

static int createProgrm(const char *vertex , const char * fragment)
{
   /* int vertexShader = loadShaders(GL_VERTEX_SHADER, vertex);//创建定点的shader
    int fragmentShader = loadShaders(GL_FRAGMENT_SHADER, fragment);//创建纹理的shader
   //3、创建一个渲染程序
    int program = glCreateProgram();
    //4、将着色器程序添加到渲染程序中
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    //5、链接源程序
    glLinkProgram(program);
    return program;*/
    int vertexShader = loadShaders(GL_VERTEX_SHADER, vertex);
    int fragmentShader = loadShaders(GL_FRAGMENT_SHADER, fragment);
    int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return program;
}

#endif //NATIVEOPENGLDEMO_WLSHADERUTIL_H
