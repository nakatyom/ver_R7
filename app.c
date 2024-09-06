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
    int16_t angle_val;
    int16_t rate_val;
    angle_val = ev3_gyro_sensor_get_angle(gyro_sensor);
    rate_val = ev3_gyro_sensor_get_rate(gyro_sensor);
    
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
        printf("counter:%d\n",toch_cnt);
    }
    else if(start_flag == false){
        toch_cnt =0;
    }
    if (start_flag == false && toch_cnt >= 200){
        start_flag=true;
        toch_cnt += 1;
    }
    else{
        printf("警告：手を放してください。\n");
    }
    if (start_flag == true &&  toch_cnt >= 1000 ){
        linetrace(val_val);
    }
    
}
