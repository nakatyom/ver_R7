#include "velocity_control.h"

#define ENC_CORR_R      1.0f        // 右ENC個体差補正係数
#define ENC_CORR_L      1.0f        // 左ENC個体差補正係数

#define TIRE_SIZE_R     94.0f       // 右タイヤ直径[mm]
#define TIRE_SIZE_L     94.0f       // 左タイヤ直径[mm]
#define TRED_SIZE       125.0f      // トレッド直径[mm]

#define SAMPLE_RATE     100.0f      // 計測周波数[sec]
#define PI_FLOAT        3.141592f   // 円周率



float mid_PID_str_velo(float tag, float maj){ 

    const float kp = 1.0f;
    const float ki = 0.0f;
    const float kd = 0.0f;

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


float mid_PID_rot_velo(float tag, float maj){ 

    const float kp = 1.0f;
    const float ki = 0.0f;
    const float kd = 0.0f;

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


void mid_velocity_control(float velo_str_tgt, float velo_rot_tgt){

    static int cnt_r;
    static int cnt_l;
    static int cnt_r_pre;
    static int cnt_l_pre;

    /* 並進速度計算 */
    cnt_r_pre = cnt_r;
    cnt_l_pre = cnt_l;
    cnt_r = ev3_motor_get_counts(right_motor); 
    cnt_l = ev3_motor_get_counts(left_motor); 

    int velo_r_tmp  = ((cnt_r - cnt_r_pre) * ENC_CORR_R) * SAMPLE_RATE; // cnt ⇒ deg/sec(motor)
    int velo_l_tmp  = ((cnt_l - cnt_l_pre) * ENC_CORR_L) * SAMPLE_RATE; // cnt ⇒ deg/sec(motor)             
    
    float velo_r    = ((float)velo_r_tmp / 360.0f) * (PI_FLOAT * TIRE_SIZE_R);   // deg/sec(motor) ⇒ mm/sec(motor) 
    float velo_l    = ((float)velo_l_tmp / 360.0f) * (PI_FLOAT * TIRE_SIZE_L);   // deg/sec(motor) ⇒ mm/sec(motor)
   
    float velo_str  = (velo_r + velo_l) * 0.5f; // mm/sec(robot)

    /* 旋回速度計算 */ 
    float velo_rot = (float)ev3_gyro_sensor_get_rate(gyro_sensor);   // deg/sec (yaw rate)

    /* 速度操作量計算（FB項算出）*/
#if (1)
    float velo_str_u = mid_PID_str_velo(velo_str_tgt, velo_str);    // mm/sec(robot)
    float velo_rot_u = mid_PID_rot_velo(velo_rot_tgt, velo_rot);    // deg/sec(yaw rate)
#else
    float velo_str_u = 0;   // debug
    float velo_rot_u = 0;   // debug
#endif

    /* 速度操作量計算（FF項とFB項の合成）*/
    float mot_r_u_str = ((velo_str_tgt + velo_str_u) / (PI_FLOAT * TIRE_SIZE_R)) * 360.0f;  // mm/sec(robot) ⇒ deg/sec(motor)
    float mot_l_u_str = ((velo_str_tgt + velo_str_u) / (PI_FLOAT * TIRE_SIZE_L)) * 360.0f;  // mm/sec(robot) ⇒ deg/sec(motor)
    float mot_r_u_rot = (TRED_SIZE / TIRE_SIZE_R) * (velo_rot_tgt + velo_rot_u);            // deg/sec(yaw rate) ⇒ deg/sec(motor)
    float mot_l_u_rot = (TRED_SIZE / TIRE_SIZE_L) * (velo_rot_tgt + velo_rot_u);            // deg/sec(yaw rate) ⇒ deg/sec(motor)
    
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

    float batt_v = (float)ev3_battery_voltage_mV();  // Todo:電圧取れない

    ev3_motor_set_power(right_motor, mot_r_u);
    ev3_motor_set_power(left_motor, mot_l_u);

    /* for Debug */
//    printf("velo_str %f | velo_rot %f | velo_str_u %f | velo_rot_u %f | mot_r_u_tmp %f | mot_l_u_tmp %f\n", velo_str, velo_rot, velo_str_u, velo_rot_u, mot_r_u_tmp, mot_l_u_tmp);
//    printf("velo_str %f | velo_rot %f | velo_str_u %f | velo_rot_u %f\n", velo_str, velo_rot, velo_str_u, velo_rot_u);
//    printf("velo_str %f | velo_rot %f\n", velo_str, velo_rot);
//    printf("cnt_r %d | cnt_l %d\n", velo_r_tmp, velo_l_tmp);
//    printf("mot_r_u_str %f | mot_r_u_rot %f\n", mot_r_u_str, mot_r_u_rot);
//    printf("mot_r_u %d | mot_l_u %d\n", mot_r_u, mot_l_u);
    printf("velo_str %8.4f | velo_rot %8.4f | mot_r_u %3d | mot_l_u %3d | batt_v %8.4f\n", velo_str, velo_rot, mot_r_u, mot_l_u, batt_v);
}
