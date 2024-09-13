#include <stdio.h>
#include <math.h>

#include "common.h"
#include "gyak_min.h"

#define GYAK_ARRAY_SIZE 11 //ジャーク最小化??��?��?割数


/* static functions */


/* external functions */
/* 最初�???��?��一回だけ呼び出される�???��?��??��?��? */
void calc_tgt(float tgt, float tgt_time, float* div_time, float* tgtV){
    int div_num = sizeof(div_time)/sizeof(div_time[0]);
    printf("div_num:%d",div_num);
    float pre_tgt_dist = 0.0;

    printf("nT:");
    /* 分割時間における */
    for(int i=1; i<=div_num; i++){
        double normTime = ((double)i / (double)div_num);             // 正規化時間
        printf("%f, ",normTime);
        div_time[i-1]  = (float)normTime * tgt_time; // 分割時間
            
        /*  */
        float tgt_dist = tgt * (float)(6.0*pow(normTime,5.0) - 15.0*pow(normTime,4.0) + 10.0*pow(normTime,3.0));

        /*  */
        if(i == 1){
            tgtV[i-1] = tgt_dist / div_time[0];
            pre_tgt_dist = tgt_dist;
        }
        else{
            tgtV[i-1] = (tgt_dist - pre_tgt_dist) / div_time[0];
            pre_tgt_dist = tgt_dist;
        }
    }

    return;
}

void get_TgtVelocity(float tgt_dist, float tgt_time, float* div_time, float* tgt_velocity){
    calc_tgt(tgt_dist, tgt_time, div_time, tgt_velocity);
    return;
}

void get_TgtRate(float tgt_theta, float tgt_time, float* div_time, float* tgt_rate){
    calc_tgt(tgt_theta, tgt_time, div_time, tgt_rate);
    return;
}
