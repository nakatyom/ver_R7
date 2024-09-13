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
    /* ポ�?�ト設�? */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    

    
    /* タスク呼び出�? */
    sta_cyc(SENS_CYC);
    //sta_cyc(BOSS_CYC);

    /* タスク終�? */
    ext_tsk();
}
int robo_mode=0;

void boss_task(intptr_t exinf){
    printf("僕�?�邪魔�?�?");
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


void sens_task(intptr_t exinf){
    /*
    left=motor_get_counts(left_motor);
    right=motor_get_counts(right_motor);
    printf("(left,right):(%d,%d) | GYRO:%d\n",left,right,gyro_sensor_get_angle(gyro_sensor));
    rgb_raw_t rgb;
    uint8_t ref = ev3_color_sensor_get_reflect(color_sensor);
    ev3_color_sensor_get_rgb_raw(color_sensor,&rgb);
    printf("ref = %d | r = %d | g = %d | b = %d\n",ref, rgb.r, rgb.g, rgb.b);
    */

   mid_velocity_control(50.0f, 0.0f);

   //gb_raw_t crnt_rgb_app = {0.0, 0.0, 0.0};

   //nt calc_luminance(rgb_raw_t color) {
   //// �?重平�?で明度を計算し、int型に変換

   //    int luminance = 0;
   //
   //    printf("r = %d, g = %d, b = %d, ",color.r,color.g,color.b);

   //    luminance = (int)(0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
   //    //luminance = (luminance * 100) / 255;

   //    printf("ref = %d\n",luminance);

   //    return luminance;
   //}

   //color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_app);
   //int ref_app = calc_luminance(crnt_rgb_app);
    
    /*else if(robo_mode == 2){
        // robo_mode = demrm
    }else if (robo_mode == 3){
        // robo_mode = smrt()
    }else{
        // robo_mode = smrt()
    }*/

}