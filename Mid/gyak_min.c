#include <stdio.h>
#include <math.h>

#include "common.h"
#include "gyak_min.h"

/* static functions */


/* external functions */
/* 最初�?????��?��??��?��???��?��??��?��一回だけ呼び出される�?????��?��??��?��???��?��??��?��????��?��??��?��???��?��??��?��? */
void calc_tgt(float tgt, float tgt_time, int div_num, float* div_dist, float* tgtV){
    float pre_div_dist = 0.0;

    /* ?��?割時間におけ?��? */
    for(int i=1; i<=div_num; i++){
        double normTime = ((double)i / (double)div_num);             // 正規化時間
        // div_time[i-1]  = (float)normTime * tgt_time; // ?��?割時間
        double div_time = normTime * tgt_time;
            
        /*  */
        div_dist[i-1] = tgt * (float)(6.0*pow(normTime,5.0) - 15.0*pow(normTime,4.0) + 10.0*pow(normTime,3.0));

        /*  */
        if(i == 1){
            tgtV[i-1] = div_dist[i-1] / div_time;
            pre_div_dist = div_dist[i-1];
        }
        else{
            tgtV[i-1] = (div_dist[i-1] - pre_div_dist) / div_time;
            pre_div_dist = div_dist[i-1];
        }
    }

    return;
}

void normalize_tgt(int div_num, float* tgt){
    float off_set = 30;
    float maxVal = tgt[div_num/2];
    float raito = off_set / maxVal;

    for(int i=0; i<div_num; i++){
        tgt[i] = (1.0 - raito)*tgt[i];
        tgt[i] += off_set;
    }

}

void calc_TgtVelocity(float tgt_dist, float tgt_time, int div_num, float* div_dist, float* tgt_velocity){
    calc_tgt(tgt_dist, tgt_time, div_num, div_dist, tgt_velocity);
    normalize_tgt(div_num, tgt_velocity);
    return;
}

void calc_TgtRate(float tgt_theta, float tgt_time, int div_num, float* div_theta, float* tgt_rate){
    calc_tgt(tgt_theta, tgt_time, div_num, div_theta, tgt_rate);
    normalize_tgt(div_num, tgt_rate);
    return;
}

float get_TgtVelcity(float crnt_dist, int div_num, float* div_dist, float* tgt_velocity){
    static int cunt_v = 0;
    /* 現在使�?べき速度配�?��?�要�?番号を更新する */
    if(div_dist[cunt_v] <= crnt_dist) cunt_v += 1;


    
    /* 配�?��?�最後に到�?(目標地点に到�?)したらリセ�?トす�?*/
    if(cunt_v >= div_num){
        cunt_v = 0;
        return 0.0;
    }

    return tgt_velocity[cunt_v];
}

float get_TgtRate(float crnt_dist, int div_num, float* div_theta, float* tgt_rate){
    static int cunt_r;
    /* 現在使�?べき速度配�?��?�要�?番号を更新する */
    if(div_theta[cunt_r] <= crnt_dist) cunt_r += 1;
    
    /* 配�?��?�最後に到�?(目標地点に到�?)したらリセ�?トす�?*/
    if(cunt_r >= div_num){
        cunt_r = 0;
        return 0.0;
    }

    return tgt_rate[cunt_r];
}
