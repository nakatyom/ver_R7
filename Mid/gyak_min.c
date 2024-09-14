#include <stdio.h>
#include <math.h>

#include "common.h"
#include "port.h"
#include "body.h"
#include "gyak_min.h"

/* static functions */


/* external functions */
/* 最初�?????��?��??��?��???��?��??��?��一回だけ呼び出される�?????��?��??��?��???��?��??��?��????��?��??��?��???��?��??��?��? */
void calc_tgt(float tgt, float tgt_time, int div_num, float* div_time, float* tgtV){
    float pre_div_dist = 0.0;

    /* ?��?割時間におけ?��? */
    for(int i=1; i<=div_num; i++){
        double normTime = ((double)i / (double)div_num);             // 正規化時間
        div_time[i-1]  = (float)normTime * tgt_time; // ?��?割時間
            
        /*  */
        float div_dist = (float)( tgt * (6.0*pow(normTime,5.0) - 15.0*pow(normTime,4.0) + 10.0*pow(normTime,3.0)) );

        /*  */
        if(i == 1){
            tgtV[i-1] = div_dist / div_time[i-1];
            pre_div_dist = div_dist;
        }
        else{
            tgtV[i-1] = (div_dist - pre_div_dist) / div_time[i-1];
            pre_div_dist = div_dist;
        }
    }

    return;
}

void normalize_tgt(int div_num, float* tgt){
    float off_set = 50.0;
    float maxVal = tgt[div_num/2];
    float raito = off_set / maxVal;

    for(int i=0; i<div_num; i++){
        //tgt[i] = (1.0 - raito)*tgt[i];
        tgt[i] += off_set;
    }

}

void calc_TgtVelocity(float tgt_dist, float tgt_time, int div_num, float* div_time, float* tgt_velocity){
    calc_tgt(tgt_dist, tgt_time, div_num, div_time, tgt_velocity);
    normalize_tgt(div_num, tgt_velocity);
    return;
}

void calc_TgtRate(float tgt_theta, float tgt_time, int div_num, float* div_time, float* tgt_rate){
    calc_tgt(tgt_theta, tgt_time, div_num, div_time, tgt_rate);
    normalize_tgt(div_num, tgt_rate);
    return;
}

float get_TgtVelcity(float crnt_time, int div_num, float* div_time, float* tgt_velocity){
    static int cunt_v = 0;
    /* 現在使�?べき速度配�?��?�要�?番号を更新する */
    if(div_time[cunt_v] <= crnt_time) cunt_v += 1;


    
    /* 配�?��?�最後に到�?(目標地点に到�?)したらリセ�?トす�?*/
    if(cunt_v >= div_num){
        cunt_v = 0;
        return 0.0;
    }

    return tgt_velocity[cunt_v];
}

float get_TgtRate(float crnt_time, int div_num, float* div_time, float* tgt_rate){
    static int cunt_r;
    /* 現在使�?べき速度配�?��?�要�?番号を更新する */
    if(div_time[cunt_r] <= crnt_time) cunt_r += 1;
    
    /* 配�?��?�最後に到�?(目標地点に到�?)したらリセ�?トす�?*/
    if(cunt_r >= div_num){
        cunt_r = 0;
        return 0.0;
    }

    return tgt_rate[cunt_r];
}


/* 関VFB移植 */ 
float gyak_PID_rot_velo(float tag, float maj){
 
    const float kp = 0.4f;
    const float ki = 0.1f;
    const float kd = 0.1f;
 
    static float intg;
    static float err_pre;
    static float err;
    err_pre = err;
    err = tag - maj;
    intg += err;
 
    if (intg > 1000.0f)    intg = 1000.0f;
    if (intg < -1000.0f)   intg = -1000.0f;
 
    return ((err * kp) + (intg * ki) + ((err - err_pre) * kd));
}
 
 
float gyak_LPF_str_velo(float maj){
 
    const float k = 0.85f;
 
    static float out;
 
    out = (out * k) + (maj * (1.0f - k));
 
    return out;
}
 
void gyak_velocity_control(float velo_str_tgt, float velo_rot_tgt){
    float enc_corr_r = 1.0;
    float enc_corr_l = 1.0;
    float sample_rate = 50.0;
    
 
    static int32_t cnt_r;
    static int32_t cnt_l;
    static int32_t cnt_r_pre;
    static int32_t cnt_l_pre;
 
    /* 並進速度計算 */
    cnt_r_pre = cnt_r;
    cnt_l_pre = cnt_l;
    cnt_r = motor_get_counts(right_motor); 
    cnt_l = motor_get_counts(left_motor);
 
    float velo_r_tmp  = (((float)(cnt_r - cnt_r_pre) * enc_corr_r) * sample_rate); // cnt ⇒ deg/sec(motor)
    float velo_l_tmp  = (((float)(cnt_l - cnt_l_pre) * enc_corr_l) * sample_rate); // cnt ⇒ deg/sec(motor)             
    float velo_r    = (velo_r_tmp / 360.0f) * (PI_FLOAT * wheel_size);   // deg/sec(motor) ⇒ mm/sec(motor) 
    float velo_l    = (velo_l_tmp / 360.0f) * (PI_FLOAT * wheel_dist);   // deg/sec(motor) ⇒ mm/sec(motor)
    float velo_str  = gyak_LPF_str_velo( ((velo_r + velo_l) * 0.5f)); // mm/sec(robot)
 
    /* 旋回速度計算 */ 
    float velo_rot = (float)ev3_gyro_sensor_get_rate(gyro_sensor);   // deg/sec (yaw rate)
 
    /* 速度操作量計算（FB項算出）*/
    // float velo_str_u = mid_PID_str_velo(velo_str_tgt, velo_str);    // mm/sec(robot)
    float velo_rot_u = gyak_PID_rot_velo(velo_rot_tgt, velo_rot);    // deg/sec(yaw rate)
 
    /* 速度操作量計算（FF項とFB項の合成）*/
    float mot_r_u_str = (velo_str_tgt / (PI_FLOAT * wheel_size)) * 360.0f;  // mm/sec(robot) ⇒ deg/sec(motor)
    float mot_l_u_str = (velo_str_tgt / (PI_FLOAT * wheel_size)) * 360.0f;  // mm/sec(robot) ⇒ deg/sec(motor)
    float mot_r_u_rot = (wheel_dist / wheel_size) * (velo_rot_tgt + velo_rot_u);            // deg/sec(yaw rate) ⇒ deg/sec(motor)
    float mot_l_u_rot = (wheel_dist / wheel_size) * (velo_rot_tgt + velo_rot_u);            // deg/sec(yaw rate) ⇒ deg/sec(motor)
    /* 速度操作量計算（並進速度と旋回速度の合成）*/
    float mot_r_u_tmp = mot_r_u_str + mot_r_u_rot;  // deg/sec(motor)
    float mot_l_u_tmp = mot_l_u_str - mot_l_u_rot;  // deg/sec(motor)
    /* 操作量計算 */
    int mot_r_u = (int)(mot_r_u_tmp * 1.0f);
    int mot_l_u = (int)(mot_l_u_tmp * 1.0f);
 
    if (mot_r_u >  100)  mot_r_u = 100;
    if (mot_r_u < -100)  mot_r_u = -100;
    if (mot_l_u >  100)  mot_l_u = 100;
    if (mot_l_u < -100)  mot_l_u = -100;
 
    ev3_motor_set_power(right_motor, mot_r_u);
    ev3_motor_set_power(left_motor, mot_l_u);
}