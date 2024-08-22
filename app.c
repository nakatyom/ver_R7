#include "app.h"
#include <stdio.h>
#include "ev3api.h"
#include "port_settings.h"


/* メインタスク(起動時にのみ関数コールされる) */
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


int ma_val;
int mv_val;
int power_left=0;
int power_right=0;
int32_t ang_left,ang_right;
int cycle_cnt=0;
void naka_task(intptr_t unused){
    //printf("10ms Task");
    //mid_linetrace_pid();
    ang_left = ev3_motor_get_counts(left_motor);
    ang_right = ev3_motor_get_counts(right_motor);



    ma_val = ev3_battery_current_mA();
    mv_val = ev3_battery_voltage_mV();
    
    if (cycle_cnt>=80){
        ev3_motor_reset_counts(left_motor);
        ev3_motor_reset_counts(right_motor);
        power_left = power_left+5;
        power_right = power_left;
        ev3_motor_set_power(left_motor, power_left);
        ev3_motor_set_power(right_motor, power_right);
        cycle_cnt=0;
    }
    printf("cnt:%d_______", cycle_cnt);
    printf("Battery(A,V):(%d,%d) | Power(L,R):(%d,%d) | Angle(L,R)=(%d,%d)\n",ma_val,mv_val,power_left,power_right,ang_left,ang_right);

    cycle_cnt=cycle_cnt+1;

}
