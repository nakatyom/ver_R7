#include <stdio.h>
#include <math.h>
#include <time.h>
#include "motor.h"
#include "ev3api.h"
#include "port.h"

// 0:Arm, 1:Right, 2:Left
int32_t crnt_enc[3] = {0, 0, 0};
int32_t pre_enc[3]  = {0, 0, 0};

int crnt_powor[3] = {0, 0, 0};
int pre_power[3]  = {0, 0, 0};

// Multiply left motor 0.0~1.0
const float motor_sync = 1.0;


/* static functions */
void delay(int milliseconds){
    clock_t start_time = clock();
    while(clock() < start_time + milliseconds);
}

/* extern functions */
extern int32_t motor_get_counts(motor_port_t tgt_port){
    if(tgt_port != EV3_PORT_A && tgt_port != EV3_PORT_B && tgt_port != EV3_PORT_C){
        printf("An invalid value entered in motor_get_counts().\n");
        return 0;
    }

    // 現在値の取得
    int32_t temp_enc = ev3_motor_get_counts(tgt_port);

    // 通信遅れ判定の場合、1ms待って再取得
    if(temp_enc == pre_enc[tgt_port] && (pre_power[tgt_port] != 0 || crnt_powor[tgt_port] != 0)){ // 前回値と一致かつモーターパワーが0でない
            delay(1); // 1ms待つ
            crnt_enc = ev3_motor_get_counts(tgt_port);
    }

    // 前回値の更新
    pre_enc[tgt_port]  = crnt_enc[tgt_port];
    crnt_enc[tgt_port] = temp_enc;

    return crnt_enc[tgt_port];
}

extern int32_t motor_get_pre_counts(motor_port_t tgt_port){
    if(tgt_port != EV3_PORT_A && tgt_port != EV3_PORT_B && tgt_port != EV3_PORT_C){
        printf("An invalid value entered in motor_get_pre_counts().\n");
        return 0;
    }

    return pre_enc[tgt_port];
}

extern void motor_reset_counts(motor_port_t tgt_port){
    ev3_motor_reset_counts(tgt_port);
    return;
}

extern void motor_set_power(motor_port_t tgt_port, int power){
    if(tgt_port != EV3_PORT_A && tgt_port != EV3_PORT_B && tgt_port != EV3_PORT_C){
        printf("An invalid value entered in motor_set_power().\n");
        return;
    }

    // 前回値の更新
    pre_power = ev3_motor_get_power(tgt_port);

    // 左モータの場合、パワーに補正をかける
    if(tgt_port == EV3_PORT_C){
        power = (int)(motor_sync * power);
    }
    
    // パワーを設定
    ev3_motor_set_power(tgt_port, power);
    return;
}

extern int  motor_get_power(motor_port_t tgt_port){
    if(tgt_port != EV3_PORT_A && tgt_port != EV3_PORT_B && tgt_port != EV3_PORT_C){
        printf("An invalid value entered in motor_get_power().\n");
        return;
    }

    return crnt_powor[tgt_port];
}

extern int  motor_get_pre_power(motor_port_t tgt_port){
    if(tgt_port != EV3_PORT_A && tgt_port != EV3_PORT_B && tgt_port != EV3_PORT_C){
        printf("An invalid value entered in motor_get__pre_power().\n");
        return;
    }
    
    return pre_powor[tgt_port];
}