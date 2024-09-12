#include <stdio.h>
#include <math.h>

#include "common.h"


/* extern functions*/
float trans_gDeg(float encdeg){
    float nPI = 360.0;

    if(abs(encdeg) > nPI){
        while(abs(encdeg) < nPI){
            nPI += 360.0;
        }
        nPI -= 360.0;
    }
    
    float deg = abs(encdeg) - nPI;
    if(encdeg < 0.0) deg *= -1.0;
    printf("(int)abs(deg):%f, (int)nPI, deg:%f\n",encdeg,nPI,deg);

    if(abs(deg) > 180.0 && abs(deg) < 360.0){
        deg = -1.0 * (360.0 - deg);
    }

    if((int)deg == -180) deg = 0.0; //floatなのでホント�?��?要な�?けど,念のため

    printf("deg:%f\n",(float)deg);
    return deg;
}

void transPolor(struct coordinate* crnt, struct coordinate* tgt, float* dist, float* theta){
    /* 現在角度をジャイロ角度に変換 */
    float crnt_gDeg = trans_gDeg(crnt->theta);
    
    /* 直進量計�? */
    float x = target->x - crnt->x;
    float y = target->y - crnt->y;
    float L = sqrt(pow(x,2.0) + pow(y, 2.0));

    /* 旋回量計�? */
    float rot = 180.0 / 3.141592 * atan2(y, x);
    rot = rot - crnt_gDeg;

    printf("直進�?:%f, 旋回角度:%f\n",L, rot);

    return;
}