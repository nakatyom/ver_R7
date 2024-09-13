#include <stdio.h>
#include <math.h>

#include "common.h"
#include "gyak_min.h"

#define GYAK_ARRAY_SIZE 11 //ã‚¸ãƒ£ãƒ¼ã‚¯æœ€å°åŒ–??¿½?¿½?å‰²æ•°


/* static functions */


/* external functions */
/* æœ€åˆï¿½???¿½?¿½ä¸€å›ã ã‘å‘¼ã³å‡ºã•ã‚Œã‚‹ï¿½???¿½?¿½??¿½?¿½? */
void calc_tgt(float tgt, float tgt_time, float* div_time, float* tgtV){
    int div_num = sizeof(div_time)/sizeof(div_time[0]);
    float pre_tgt_dist = 0.0;

    /* ??¿½?¿½?æ™‚é–“ã«ãŠã‘ã‚‹ç›®æ¨™è·é›¢ã‚’ï¿½???¿½?¿½??¿½?¿½???¿½?¿½ã«æ ¼ç´ã™??¿½?¿½? */
    for(int i=1; i<=div_num; i++){
        double normTime = (i / div_num);      // æ­£è¦åŒ–æ™‚é–“
        div_time[i-1]  = normTime * tgt_time; // ??¿½?¿½?å‰²æ™‚é–“
            
        /* ??¿½?¿½???¿½?¿½?å‰²æ™‚é–“ã«ãŠã‘ã‚‹ç›®æ¨™è·é›¢ã®è¨ˆï¿½? */
        float tgt_dist = tgt * (float)(6.0*pow(normTime,5.0) - 15.0*pow(normTime,4.0) + 10.0*pow(normTime,3.0));

        /* ç›®æ¨™é€Ÿåº¦ã‚’è¨ˆï¿½? */
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
