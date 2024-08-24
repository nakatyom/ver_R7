#include <stdio.h>

#include "app.h"
#include "ev3api.h"
#include "port.h"

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
    /* IOポート設定 */
    // sensor: touch_sensor,color_sensor, sonar_sensor, gyro_sensor
    // motor : arm_motor, left_motor, right_motor
    set_ports();

    /* タスク呼び出し */
    sta_cyc(BOSS_CYC);

    /* タスク終了 */
    ext_tsk();
}

int a = 0;

void boss_task1(){
    if(a <= 50){
        sta_cyc(ICHI_CYC1);
    }
    else if(a > 50 && a <= 100){
        sta_cyc(ICHI_CYC2);
    }
    else {
        ext_tsk();
    }
}

void ichi_task1(intptr_t exinf){
    if(a == 50){
        ext_tsk();
    }

    printf("aaa, %d\n", a);
    a += 1;
}

void ichi_task2(intptr_t exinf){
    printf("bbb, %d\n",a);
    a += 1;
}
