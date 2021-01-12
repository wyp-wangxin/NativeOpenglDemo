//
// Created by yangw on 2019-3-31.
//

#ifndef NATIVEOPENGLDEMO_WLBASEOPENGL_H
#define NATIVEOPENGLDEMO_WLBASEOPENGL_H


#include <GLES2/gl2.h>
#include <cstring>
#include "../log/WlAndroidLog.h"

class WlBaseOpengl {

public:

    int surface_width;
    int surface_height;

    char * vertex;
    char * fragment;

    float *vertexs;
    float *fragments;

    GLuint program;

public:
    WlBaseOpengl();
    ~WlBaseOpengl();

    virtual void onCreate();

    virtual void onChange(int w, int h);

    virtual void draw();

    virtual void destroy();

    virtual void setPilex(void *data, int width, int height, int length);



};


#endif //NATIVEOPENGLDEMO_WLBASEOPENGL_H
