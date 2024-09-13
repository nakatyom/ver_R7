#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ev3api.h"
#include "common.h"
#include "body.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"
#include "odometry.h"

#define PI_FLOAT_    3.141592f   // 円周率

static struct coordinate pre_coordinate  = {0.0, 0.0, 0.0}; //前回座標

/* external functions */
void get_crntCoordinate(struct coordinate* crnt_coordinate){
    float delta_L = 0.0; // 移動量

    /* 左右モータの回転量を計算する[rad] */
    float delta_PhL = PI_FLOAT_ * (float)(motor_get_counts(left_motor)  - motor_get_pre_counts(left_motor))  / 180.0;
    float delta_PhR = PI_FLOAT_ * (float)(motor_get_counts(right_motor) - motor_get_pre_counts(right_motor)) / 180.0;
    // printf("delta_PhL:%f | delta_PhR:%f | ",delta_PhL,delta_PhR);
    
    /* 左右モータの移動量を計算する */
    float delta_LL = (float)(wheel_size / 2) * delta_PhL;
    float delta_LR = (float)(wheel_size / 2) * delta_PhR;

    // 走行体の旋回角度を計算する(エンコーダー)
    float delta_rad_e = 0.0;
    float delta_theta_e = 0.0;

    if(delta_LL > 0.0 && delta_LR < 0.0){ //時計回りに旋回している
        //ロボットの移動距離
        delta_L = 0.0;
        // 旋回量の計算
        delta_rad_e = -1.0 * (abs(delta_LL) + abs(delta_LR)) / (float)wheel_dist;

    }
    else if((delta_LL < 0.0 && delta_LR > 0.0)){ // 反時計回りに旋回している
        //ロボットの移動距離
        delta_L = 0.0;
        // 旋回量の計算
        delta_rad_e = (abs(delta_LL) + abs(delta_LR)) / (float)wheel_dist;

    }
    else { //直進・曲進している
        //ロボットの移動距離
        delta_L = (delta_LL + delta_LR)/(float)2.0;
        //ロボットの旋回量
        delta_rad_e = (delta_LL - delta_LR) / (float)wheel_dist;
        
        if(abs(delta_rad_e) > 0.174){ //delta_rad_eが十分大きい
            delta_L = 2.0 * (delta_L / delta_rad_e) * sin(delta_rad_e / 2.0);
        }
        
    }
    delta_theta_e = (delta_rad_e * 180.0 / PI_FLOAT_);

    /* 走行体の旋回角度を計算する (ジャイロ)*/
    float delta_theta_g = (float)(gyro_sensor_get_angle(gyro_sensor) - gyro_sensor_get_pre_angle(gyro_sensor));
    float delta_rad_g   = PI_FLOAT_ * delta_theta_g /180.0;

    // 現在座標を計算する
    float pre_rad = PI_FLOAT_ * pre_coordinate.theta / 180.0;
    float delta_rad = delta_rad_e;      // 旋回量計算に使用するデバイスの選択
    float delta_theta = delta_theta_e;  // 旋回量計算に使用するデバイスの選択

    crnt_coordinate->x      = pre_coordinate.x + (float)(delta_L * cos( pre_rad + (delta_rad / 2.0) ));
    crnt_coordinate->y      = pre_coordinate.y + (float)(delta_L * sin( pre_rad + (delta_rad / 2.0) ));
    crnt_coordinate->theta  = pre_coordinate.theta + (float)delta_theta;
    
    //前回座標を更新する
    pre_coordinate.x     = crnt_coordinate->x;
    pre_coordinate.y     = crnt_coordinate->y;
    pre_coordinate.theta = crnt_coordinate->theta;

    return;
}

extern void get_preCoordinate(struct coordinate* coordinate_p){
    coordinate_p->x     = pre_coordinate.x;
    coordinate_p->y     = pre_coordinate.y;
    coordinate_p->theta = pre_coordinate.theta;

    return;
}

