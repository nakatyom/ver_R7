#include <stdio.h>
#include <math.h>

#include "common.h"
#include "gyak_min.h"

#define GYAK_ARRAY_SIZE 11 //ジャーク最小化分割数


/* static functions */


/* external functions */
/* 最初の一回だけ呼び出される処理 */
void calc_tgt(float tgt, float tgt_time, float* div_time, float* tgtV){
    int div_num = sizeof(div_time)/sizeof(div_time[0]);

    /* 各時間における目標距離を配列に格納する */
    for(int i=1; i<=div_num; i++){
        float normTime = (i / div_num);      // 正規化時間
        div_time[i-1]  = normTime * tgt_time; // 分割時間
            
        /* 各分割時間における目標距離の計算 */
        float tgt_dist = tgt * (float)(6.0*pow(normTime,5.0) - 15.0*pow(normTime,4.0) + 10.0*pow(normTime,3.0));

        /* 目標速度を計算 */
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
