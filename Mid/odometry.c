#include <math.h>
#include <stdlib.h>

#include "ev3api.h"
#include "body.h"
#include "port.h"
#include "motor.h"
#include "odometry.h"

struct coordinate pre_coordinate  = {0,0,0};

float delta_LL = 0.0; // 左タイヤの移動距離
float delta_LR = 0.0; // 右タイヤの移動距離
int   straight_threshold = 2; //直進時のモータ角度誤差許容範囲
float delta_theta_thresshold = 0.0;

float delta_L     = 0.0; // ロボットの移動距離
float delta_theta = 0.0; // ロボットの旋回量
double delta_rad  = 0.0; // ロボットの旋回量(radian)

/* external functions */
void get_crntCoordinate(struct coordinate* crnt_coordinate){

    //左右モータの回転量を計算する[rad]
    float delta_PhL = 3.141592*(motor_get_counts(left_motor)-motor_get_pre_counts(left_motor))/180.0;
    float delta_PhR = 3.141592*(motor_get_counts(right_motor)-motor_get_pre_counts(right_motor))/180.0;
    /* 左右モータの移動量を計算する */
    delta_LL = (float)wheel_size/2 * delta_PhL;
    delta_LR = (float)wheel_size/2 * delta_PhR;

    if(delta_LL > 0.0 && delta_LR < 0.0 || delta_LL < 0.0 && delta_LR > 0.0){ //旋回している
        //ロボットの移動距離
        delta_L = 0.0;

        // 旋回量の計算(左右移動量の平均をwheel_dis/2で割る)
        delta_rad = (delta_LL+delta_LR)/whell_dist;

    }
    else { //直進・曲進している
        //ロボットの移動距離
        delta_L = (delta_LL + delta_LR)/(float)2.0;

        if( (abs(delta_LL)-abs(delta_LR)) < (47.0*3.141592*straight_threshold/180.0) ){ //直進している
            //ロボットの旋回量
            delta_rad = 0.0;

        }
        else { //曲進している
            //ロボットの旋回量
            delta_rad = (delta_LL - delta_LR)/(float)whell_dist;

            if(delta_rad > delta_theta_thresshold){ //delta_thetaが大きい
                delta_L = 2*(delta_L/delta_rad)*sin(delta_rad/2);
            }

        }

    }

    // 現在座標を計算する
    double pre_rad = 3.141592*pre_coordinate.theta/180.0;
    crnt_coordinate->x = pre_coordinate.x + (int)( (double)delta_L * cos(pre_rad+delta_rad/2) );
    crnt_coordinate->y = pre_coordinate.x + (int)( (double)delta_L * sin(pre_rad+delta_rad/2) );
    delta_theta = 180.0*delta_rad/3.141592;
    crnt_coordinate->theta = pre_coordinate.theta + (int)delta_theta;
    
    //前回座標を更新する
    pre_coordinate.x     = crnt_coordinate->x;
    pre_coordinate.y     = crnt_coordinate->y;
    pre_coordinate.theta = crnt_coordinate->theta;

}

