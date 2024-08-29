#include <math.h>
#include "ev3api.h"
#include "port.h"
#include "motor.h"
#include "odometry.h"

extern struct coordinate crnt_coordinate = {0,0,0};
extern struct coordinate pre_coordinate  = {0,0,0};

float delta_LL    = 0.0; // 左タイヤの移動距離
float delta_LR    = 0.0; // 右タイヤの移動距離

float delta_L     = 0.0; // ロボットの移動距離
float delta_theta = 0.0; //ロボットの旋回量

/* external functions */
coordinate get_crntCoordinate(){
    /* 左右モータの移動量を計算する */
    int32_t delta_PhL = motor_get_counts(left_motor)-motor_get_pre_counts(left_motor);
    int32_t delta_PhR = motor_get_counts(right_motor)-motor_get_pre_counts(right_motor);
    delta_LL = (float)( (float)(wheel_size/2) * delta_PhL );
    delta_LR = (float)( (float)(wheel_size/2) * delta_PhR );

    //ロボットの移動距離
    delta_L = (delta_LL + delta_LR)/(float)2.0;
    //ロボットの旋回量
    delta_theta = (delta_LL - delta_LR)/(float)whell_dist;

    // 現在座標を計算する
    double rad = 3.141592 * (double)delta_theta / 180.0;
    crnt_coordinate.x = pre_coordinate.x + (int)( (double)delta_L * cos(rad) );
    crnt_coordinate.y = pre_coordinate.x + (int)( (double)delta_L * sin(rad) );
    crnt_coordinate.delta_theta = pre_coordinate.delta_theta + (int)delta_L;
    
}
