#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"
#include "app.h"
#include "odometry.h"
#include "dbleRoop.h"
#include "linetrace.h"

/* メインタスク */
void main_task(intptr_t unused) {
    /* ポート設定 */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    /* タスク呼び出し */
    sta_cyc(SENS_CYC);
    //sta_cyc(BOSS_CYC);

    /* タスク終了 */
    ext_tsk();
}


void boss_task(intptr_t exinf){
    printf("僕は邪魔者。");
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
int32_t left=0;
int32_t right=0;
int robo_mode=1;
struct coordinate postest = {0.0, 0.0, 0.0};//自己位置座標
void sens_task(intptr_t exinf){
    //get_crntCoordinate(&postest);
    //printf("x=%f, y=%f, theta(変換後)=%f° | ",postest.x, postest.y, trans_gDeg(postest.theta));

    /*
    left=motor_get_counts(left_motor);
    right=motor_get_counts(right_motor);
    printf("(left,right):(%d,%d) | GYRO:%d\n",left,right,gyro_sensor_get_angle(gyro_sensor));
    rgb_raw_t rgb;
    uint8_t ref = ev3_color_sensor_get_reflect(color_sensor);
    ev3_color_sensor_get_rgb_raw(color_sensor,&rgb);
    printf("ref = %d | r = %d | g = %d | b = %d\n",ref, rgb.r, rgb.g, rgb.b);
    */
    //printf("\n(mA,mV):(%d,%d)  |  ",ev3_battery_current_mA(),ev3_battery_voltage_mV());
    if (robo_mode == 0 ){
        robo_mode = linetrace();
    }else if(robo_mode == 1){
        //printf("NEO  ");
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