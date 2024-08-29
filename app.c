#include <stdio.h>

#include "app.h"
#include "ev3api.h"
#include "port.h"
#include "linetrace.h"
#include "get_line.h"

/* メインタスク(起動時にのみ関数コールされ�?) */
void main_task(intptr_t unused) {
    
    /* タスク呼び出�? */
    sta_cyc(LT_CYC);

    /* タスク終�? */
    ext_tsk();
}

int is_touch = 0;

void linetrace_task(intptr_t exinf){
    if(ev3_touch_sensor_is_pressed(touch_sensor)){
       is_touch  = 1;
    }

    if(is_touch == 1){
        // get_line();
        linetrace();
    }
}