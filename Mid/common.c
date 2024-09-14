#include <stdio.h>
#include <math.h>

#include "common.h"


/* extern functions*/
float trans_gDeg(float encdeg){
    float nPI = 0.0;

    //n周回分引く
    while(fabs(encdeg) > (nPI + 360.0)){
        //printf(" | %f | encdeg:%f ",nPI,encdeg);
        nPI += 360.0;
    }
    //printf("\n");
    float deg = fabs(encdeg) - nPI;

    //角度の符号を戻す
    if(encdeg < 0.0) deg *= -1.0;
    //printf("(int)abs(deg):%f, (int)nPI:%f, deg:%f\n",encdeg,nPI,deg);
    
    /* 181~360 -> -179~0 */
    if(fabs(deg) > 180.0 && fabs(deg) <= 360.0){
        deg = -1.0 * (360.0 - deg);
    }

    //printf("deg:%f\n",(float)deg);
    return deg;
}

float get_dist_p(struct coordinate* crnt, struct coordinate* trgt){
    /* 現在角度をジャイロ角度に変換 */
    float crnt_gDeg = trans_gDeg(crnt->theta);
    
    /* 距離計算 */
    float x = trgt->x - crnt->x;
    float y = trgt->y - crnt->y;
    float dist = sqrt(pow(x,2.0) + pow(y, 2.0));

    //printf("dist:%f",dist);
    return dist;
}

int get_rot_p(struct coordinate* crnt, struct coordinate* trgt){
    float x = trgt->x - crnt->x;
    float y = trgt->y - crnt->y;

    /* 現在角度をジャイロ角度に変換 */
    float crnt_gDeg = trans_gDeg(crnt->theta);

    /* 旋回量計算 */
    float rot = 180.0 / 3.141592 * atan2(y, x);
    rot = rot - crnt_gDeg;

    //printf("rot:%d\n"rot);
    return (int)rot;
}

