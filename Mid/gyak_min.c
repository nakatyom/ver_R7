#include <stdio.h>
#include <math.h>

#include "common.h"
#include "gyak_min.h"

#define GYAK_ARRAY_SIZE 11 //ジャーク最小化�?割数


/* static functions */


/* external functions */
/* 最初�?�一回だけ呼び出される�?��? */
void calc_tgt(float tgt, float tgt_time, float* div_time, float* tgtV){
    int div_num = sizeof(div_time)/sizeof(div_time[0]);

    /* �?時間における目標距離を�?��?�に格納す�? */
    for(int i=1; i<=div_num; i++){
        double normTime = (i / div_num);      // 正規化時間
        div_time[i-1]  = normTime * tgt_time; // �?割時間
            
        /* �?�?割時間における目標距離の計�? */
        float tgt_dist = tgt * (float)(6.0*pow(normTime,5.0) - 15.0*pow(normTime,4.0) + 10.0*pow(normTime,3.0));

        /* 目標速度を計�? */
        if(i == 1){
            tgtV[i-1] = div_dist[i-1] / div_time[0];
        }
        else{
            tgtV[i-1] = (div_dist[i-1] - div_dist[i-1]) / div_time[0];
        }
    }

    return;
}

void get_TgtVelocity(float tgt_dist, float tgt_time, float* div_time, float* tgt_velocity){
    calc_tgt(tgt_dist, tgt_time, div_time, tgt_velocity);
    return;
}

void get_TgtRate(float tgt_theta, float tgt_time, float* div_time, float* tgt_rate){
    calc_tgt(tgt_dist, tgt_time, div_time, tgt_rate);
    return;
}
