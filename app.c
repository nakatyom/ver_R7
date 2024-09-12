#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "port.h"
#include "motor.h"
#include "gyro.h"
#include "app.h"
#include "odometry.h"
#include "gyak_min.h"

/* メインタスク */
void main_task(intptr_t unused) {
    /* ポ�?�ト設�? */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    /* タスク呼び出�? */
    sta_cyc(SENS_CYC);
    sta_cyc(BOSS_CYC);

    /* タスク終�? */
    ext_tsk();
}

#include <math.h>
struct coordinate crnt   = {  0.0,   0.0, 0.0};
struct coordinate target = {100.0, 100.0, 0.0}; // 地点座標なので角度な�?

double trans_gDeg(double encdeg); // 任意センサ角度→ジャイロ角度

void boss_task(intptr_t exinf){
    static int is_head;

    if(0 == is_head){
        /* 現在角度をジャイロ角度に変換 */
        double crnt_gDeg = trans_gDeg(crnt.theta);
        
        /* 直進量計�? */
        double x = target.x - crnt.x;
        double y = target.y - crnt.y;

        double L = sqrt(pow(x,2.0) + pow(y, 2.0));

        /* 旋回量計�? */
        double rot = 180.0 / 3.141592 * atan2(y, x);
        printf("tan2:%f",(float)rot);
        rot = rot - crnt_gDeg;

        printf("直進�?:%f, 旋回角度:%f\n",(float)L, (float)rot);

        is_head = 1;
    }
}

double trans_gDeg(double encdeg){
    double nPI = 360.0;

    if(abs(encdeg) > nPI){
        while(abs(encdeg) < nPI){
            nPI += 360.0;
        }
        nPI -= 360.0;
    }
    
    double deg = (double)(abs((int)encdeg) % (int)nPI);
    printf("deg:%f\n",(float)deg);

    if(encdeg < 0.0) deg *= -1.0;

    if(abs(deg) > 180.0 && abs(deg) < 360.0){
        deg = -1.0 * (360.0 - deg);
    }

    if((int)deg == -180) deg = 0.0; // �?が一の処�?�?らんかも

    printf("deg:%f\n",(float)deg);
    return deg;
}


void sens_task(intptr_t exinf){
    /* モータ読み取り */
    // motor_update(arm_motor);
    // motor_update(left_motor);
    // motor_update(right_motor);

    /* ジャイロ読み取り */
    // gyro_sensor_update(gyro_sensor);

    /* カラーセンサ読み取り */
    // color_sensor_update(color_sensor);

}