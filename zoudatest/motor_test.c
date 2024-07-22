#ifndef motor_test_H
#define motor_test_H

#include "ev3api.h"
//#include "etroboc_ext.h"

#include <stdio.h>

//関数プロトタイプ宣言
static void motorLog();



/* ステアリング操舵量の計算 */
static void motorTypeLog(){
    printf("left_motor's port is %d, and it's power is %d \n",ev3_motor_get_type(left_motor),ev3_motor_get_power(left_motor));
    printf("right_motor's port is %d, and it's power is %d \n",ev3_motor_get_type(right_motor),ev3_motor_get_type(right_motor););
}

#endif