#include <stdio.h>

#include "ev3api.h"

#include "common.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"


#include "odometry.h"
#include "velocity_control.h"
#include "gyak_min.h"

#include "linetrace.h"
#include "dbNeo.h"
#include "app.h"

/* メインタスク */
void main_task(intptr_t unused) {
    /* ポート設定 */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
 
    /* タスク呼び出し */
    sta_cyc(SENS_CYC);

    /* タスク終了 */
    ext_tsk();
}

void boss_task(intptr_t exinf){}

void sens_task(intptr_t exinf){
    static int is_start = 0;
    if(ev3_touch_sensor_is_pressed(touch_sensor)){
        is_start = 1;
    }
    else if(1 == is_start){
        printf("start!!!\n");
        is_start = 2;
    }
    else if(2 == is_start){
        static int robo_mode = 0;

        if (robo_mode == 0 ){
            robo_mode = linetrace();
        }
        else if(robo_mode == 1){
            robo_mode = hello_neo();
        }
        else if(robo_mode == 2){
            robo_mode = hello_dmrm();
        }
        else if (robo_mode == 3){
            // robo_mode = hello_carry();
        }
        else{
            printf("完\n");
        }
    }
    else {}

}