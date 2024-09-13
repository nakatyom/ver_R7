#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"
#include "app.h"
#include "odometry.h"
#include "smartCarry.h"
#include "linetrace.h"

/* メインタスク */
void main_task(intptr_t unused) {
    /* ポート設定 */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    /* タスク呼び出し */
    sta_cyc(SENS_CYC);
    sta_cyc(BOSS_CYC);

    /* タスク終了 */
    ext_tsk();
}
int robo_mode=0;

void boss_task(intptr_t exinf){
    /*
    static struct coordinate crnt;
    get_crntCoordinate(&crnt);
    if (robo_mode == 0 ){
        robo_mode = linetrace();
    }else if(robo_mode == 1){
        robo_mode = hello_neo();
    }/*else if(robo_mode == 2){
        // robo_mode = demrm
    }else if (robo_mode == 3){
        // robo_mode = smrt()
    }else{
        // robo_mode = smrt()
    }*/

    
}

void sens_task(intptr_t exinf){
    if (robo_mode == 0 ){
        robo_mode = linetrace();
    }else if(robo_mode == 1){
        printf("NEO  ");
        robo_mode = hello_neo();
    }
    /*else if(robo_mode == 2){
        // robo_mode = demrm
    }else if (robo_mode == 3){
        // robo_mode = smrt()
    }else{
        // robo_mode = smrt()
    }*/

}