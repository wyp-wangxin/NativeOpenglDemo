//
// Created by yangw on 2019-3-10.
//

#ifndef NATIVEOPENGLDEMO_MATRIXUTIL_H
#define NATIVEOPENGLDEMO_MATRIXUTIL_H

#include <math.h>
static void initMatrix(float *matrix)
{
    for(int i = 0; i < 16; i++)
    {
        if(i % 5 == 0)
        {
            matrix[i] = 1;
        } else{
            matrix[i] = 0;
        }
    }
}

static void rotateMatrix(double angle, float *matrix)
{
    angle = angle * (M_PI / 180.0); //转化为弧度

    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);

}
#endif //NATIVEOPENGLDEMO_MATRIXUTIL_H
