#include <stdio.h>
#include <math.h>

#include "common.h"
#include "gyak_min.h"

#define GYAK_ARRAY_SIZE 11 //ã‚¸ãƒ£ãƒ¼ã‚¯æœ€å°åŒ–???¿½?¿½??¿½?¿½?å‰²æ•°


/* static functions */


/* external functions */
/* æœ€åˆï¿½????¿½?¿½??¿½?¿½ä¸€å›ã ã‘å‘¼ã³å‡ºã•ã‚Œã‚‹ï¿½????¿½?¿½??¿½?¿½???¿½?¿½??¿½?¿½? */
void calc_tgt(float tgt, float tgt_time, int div_num, float* div_time, float* tgtV){
    printf("div_num:%zu",div_num);
    float pre_tgt_dist = 0.0;

    printf("nT:");
    /* åˆ?å‰²æ™‚é–“ã«ãŠã‘ã‚? */
    for(int i=1; i<=div_num; i++){
        double normTime = ((double)i / (double)div_num);             // æ­£è¦åŒ–æ™‚é–“
        printf("%f, ",normTime);
        div_time[i-1]  = (float)normTime * tgt_time; // åˆ?å‰²æ™‚é–“
            
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

void get_TgtVelocity(float tgt_dist, float tgt_time, int div_num, float* div_time, float* tgt_velocity){
    calc_tgt(tgt_dist, tgt_time, div_num, div_time, tgt_velocity);
    return;
}

void get_TgtRate(float tgt_theta, float tgt_time, int div_num, float* div_time, float* tgt_rate){
    calc_tgt(tgt_theta, tgt_time, div_num, div_time, tgt_rate);
    return;
}
