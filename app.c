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

void boss_task(intptr_t exinf){
    struct coordinate crnt;
    get_crntCoordinate(&crnt);

    printf("x=%d, y=%d, theta=%d\n",crnt.x, crnt.y,crnt.theta);
}