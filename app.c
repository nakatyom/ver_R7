#include <stdio.h>

#include "app.h"
#include "ev3api.h"
#include "port.h"
#include "odometry.h"

/* メインタスク(起動時にのみ関数コールされ�?) */
void main_task(intptr_t unused) {
    /* ポート設定 */
    // sensor   : touch_sensor, color_sensor, sonar_sensor, gyro_sensor
    // actuator : arm_motor, left_motor, right_motor
    set_portCfg();
    
    /* タスク呼び出し */
    sta_cyc(BOSS_CYC);

    /* タスク終了 */
    ext_tsk();
}

#include "body.h"

void boss_task(intptr_t exinf){
    struct coordinate crnt = {0.0, 0.0, 0.0};
    get_crntCoordinate(&crnt);

    printf("x=%f, y=%f, theta=%f\n",crnt.x, crnt.y,crnt.theta);

    // int16_t angle = gyro_sensor_get_angle(gyro_sensor);
    // int16_t rate  = gyrosensor_get_rate(gyro_sensor);
    // printf("theta = %d\n", angle);

}