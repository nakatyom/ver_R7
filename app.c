#include "app.h"
#include "list_api.h"
#include <stdio.h>
#include "ev3api.h"
#include <float.h>

#include "battery.h"

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {
    
    printf("Start MainTask!!\n");
    /* write_log(); */
    commn_settings();    
    

    printf("Start Ichi Task!!\n");
    sta_cyc(ICHI_CYC);


    /* タスク終了 */
    ext_tsk();
}

void ichi_task(intptr_t exinf){
    float V = ((float)(get_batV())/1000);
    float C = ((float)(get_batC())/1000);

    printf("bat_vol is %f : ", V);
    printf("bat_crr is %f : ", C);
    printf("\n");

}