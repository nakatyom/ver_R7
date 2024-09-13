#include <stdio.h>
#include <math.h>

#include "common.h"


/* extern functions*/
float trans_gDeg(float encdeg){
    float nPI = 0.0;

    //何周したか数える
    while(fabs(encdeg) > (nPI + 360.0)){
        printf(" | %f | encdeg:%f ",nPI,encdeg);
            nPI += 360.0;
    }
    printf("\n");
    //nPI周を引く
    float deg = fabs(encdeg) - nPI;

    //回転方向を戻す
    if(encdeg < 0.0) deg *= -1.0;
    //printf("(int)abs(deg):%f, (int)nPI:%f, deg:%f\n",encdeg,nPI,deg);
    
    if(fabs(deg) > 180.0 && fabs(deg) < 360.0){
        deg = -1.0 * (360.0 - deg);
    }

    if(deg == -180.0) deg = 0.0; //floatなのでホント�?��?要な�?けど,念のため

    //printf("deg:%f\n",(float)deg);
    return deg;
}

void transPolor(struct coordinate* crnt, struct coordinate* trgt, float* dist, float* theta){
    /* 現在角度をジャイロ角度に変換 */
    float crnt_gDeg = trans_gDeg(crnt->theta);
    
    /* 直進量計�? */
    float x = trgt->x - crnt->x;
    float y = trgt->y - crnt->y;
    float L = sqrt(pow(x,2.0) + pow(y, 2.0));

    /* 旋回量計�? */
    float rot = 180.0 / 3.141592 * atan2(y, x);
    rot = rot - crnt_gDeg;

    //printf("直進�?:%f, 旋回角度:%f\n",L, rot);

    return;
}