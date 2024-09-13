#include <stdio.h>
#include <math.h>

#include "common.h"
#include "gyak_min.h"

#define GYAK_ARRAY_SIZE 11 //ã‚¸ãƒ£ãƒ¼ã‚¯æœ€å°åŒ–????¿½?¿½??¿½?¿½???¿½?¿½??¿½?¿½?å‰²æ•°


/* static functions */


/* external functions */
/* æœ€åˆï¿½?????¿½?¿½??¿½?¿½???¿½?¿½??¿½?¿½ä¸€å›ã ã‘å‘¼ã³å‡ºã•ã‚Œã‚‹ï¿½?????¿½?¿½??¿½?¿½???¿½?¿½??¿½?¿½????¿½?¿½??¿½?¿½???¿½?¿½??¿½?¿½? */
void calc_tgt(float tgt, float tgt_time, int div_num, float* div_time, float* tgtV){
    float pre_tgt_dist = 0.0;

    /* ?¿½?å‰²æ™‚é–“ã«ãŠã‘?¿½? */
    for(int i=1; i<=div_num; i++){
        double normTime = ((double)i / (double)div_num);             // æ­£è¦åŒ–æ™‚é–“
        div_time[i-1]  = (float)normTime * tgt_time; // ?¿½?å‰²æ™‚é–“
            
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

void calc_TgtVelocity(float tgt_dist, float tgt_time, int div_num, float* div_time, float* tgt_velocity){
    calc_tgt(tgt_dist, tgt_time, div_num, div_time, tgt_velocity);
    return;
}

void calc_TgtRate(float tgt_theta, float tgt_time, int div_num, float* div_time, float* tgt_rate){
    calc_tgt(tgt_theta, tgt_time, div_num, div_time, tgt_rate);
    return;
}

float get_TgtVelcity(float crnt_time, int div_num, float* div_time, float* tgt_velocity){
    static int cunt_v = 0;
    /* ç¾åœ¨ä½¿ã?ã¹ãé€Ÿåº¦é…å?—ã?®è¦ç´?ç•ªå·ã‚’æ›´æ–°ã™ã‚‹ */
    if(div_time[cunt_v] <= crnt_time) cunt_v += 1;
    
    /* é…å?—ã?®æœ€å¾Œã«åˆ°é?(ç›®æ¨™åœ°ç‚¹ã«åˆ°é?)ã—ãŸã‚‰ãƒªã‚»ãƒ?ãƒˆã™ã‚?*/
    if(cunt_v >= div_num){
        cunt_v = 0;
        return 0.0;
    }

    return tgt_velocity[cunt_v];
}

float get_TgtRate(float crnt_time, int div_num, float* div_time, float* tgt_rate){
    static int cunt_r;
    /* ç¾åœ¨ä½¿ã?ã¹ãé€Ÿåº¦é…å?—ã?®è¦ç´?ç•ªå·ã‚’æ›´æ–°ã™ã‚‹ */
    if(div_time[cunt_r] <= crnt_time) cunt_r += 1;
    
    /* é…å?—ã?®æœ€å¾Œã«åˆ°é?(ç›®æ¨™åœ°ç‚¹ã«åˆ°é?)ã—ãŸã‚‰ãƒªã‚»ãƒ?ãƒˆã™ã‚?*/
    if(cunt_r >= div_num){
        cunt_r = 0;
        return 0.0;
    }

    return tgt_rate[cunt_r];
}
