#include "app.h"
#include "ev3api.h"
#include <stdio.h>

#include "port.h"
#include "Log.h"

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

    /* ポート設定 */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor 
    // actuator : arm_motor, left_motr, right_motor
    set_portCfg();
    
    printf("Start LogTask!!\n");
    sta_cyc(LOG_CYC);


    /* タスク終了 */
    ext_tsk();
}

int motor_p = 50;
int32_t encL = 0;
int32_t encR = 0;
int is_head = 0;


void log_task(intptr_t unused){

    if(is_head == 0){
        ev3_motor_reset_counts(left_motor);
        ev3_motor_reset_counts(right_motor);
        is_head = 1;
    }

    // ev3_motor_set_power(left_motor,motor_p);
    // ev3_motor_set_power(right_motor,motor_p);

    encL = ev3_motor_get_counts(left_motor);
    encR = ev3_motor_get_counts(right_motor);

    printf("%ld,%ld\n",encL,encR);
    //log_EncLR(motor_p,motor_p,encL,encR);
}
