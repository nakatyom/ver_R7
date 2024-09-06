#include "app.h"
#include <stdio.h>
#include "ev3api.h"
#include "port_settings.h"
#include "linetrace.h"
#include "velocity_control.h"

/* メインタスク(起動時にのみ関数コールされる) */
bool_t toch_flg = false;
void main_task(intptr_t unused) {

    printf("Start MainTask!!\n");
    
    /* ライントレースタスクの起動 */
    /* write_log(); */
    commn_settings();
    printf("Start Naka Task!!\n");
    sta_cyc(NAKA_TASK_CYC);

    /* タスク終了 */
    ext_tsk();
}

int toch_cnt = 0; 
bool_t pre_toch=false;
bool_t start_flag = false;
float val_val=0.0;
//uint8_t cnt;
void naka_task(intptr_t unused){
    // printf("10ms Task ");
    pre_toch = toch_flg;
    toch_flg = ev3_touch_sensor_is_pressed(touch_sensor);
    
    if (pre_toch == false && toch_flg==true){
        val_val = val_val + 0.01;
        printf("変数値：%f\n",val_val);
    }else{
        printf(".");
    }

    if (start_flag == false && toch_flg == true){
        toch_cnt += 1;
    }
    else{
        toch_cnt =0;
    }

    if (start_flag == false && toch_cnt >= 200){
        start_flag=true;
    }
    if (start_flag == true){
        linetrace(val_val);
    }
}
