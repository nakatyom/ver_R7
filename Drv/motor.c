#include <stdio.h>
#include "ev3api.h"
#include "port.h"
#include "motor.h"

int32_t crnt_encL = 0;
int32_t crnt_encR = 0;
int32_t crnt_encA = 0;
int32_t pre_encL = 0;
int32_t pre_encR = 0;
int32_t pre_encA = 0;
const  float motor_balancer = 1.0;   // Multiply left motor 0.0~1.0

/* extern functions */
extern void motor_set_power(motor_port_t tgt_port, int power){
    if(tgt_port == EV3_PORT_C){
        power = (int)(motor_balancer * power);
    }
    else if(tgt_port == EV3_PORT_B || tgt_port == EV3_PORT_A){
        // 何もしない
    }
    else {
        printf("An invalid value entered in motor_get_pre_counts.\n");
        return;
    }
    
    ev3_motor_set_power(tgt_port, power);
}

extern int  motor_get_power(motor_port_t tgt_port){
    return ev3_motor_get_power(tgt_port);
}

extern void motor_reset_counts(motor_port_t tgt_port){
    ev3_motor_reset_counts(tgt_port);
}

extern int32_t motor_get_counts(motor_port_t tgt_port){
    if(tgt_port == EV3_PORT_C){
        pre_encL  = crnt_encL;
        crnt_encL = ev3_motor_get_counts(tgt_port);
        
        return crnt_encL;
    }
    else if(tgt_port == EV3_PORT_B){
        pre_encR  = crnt_encR;
        crnt_encR = ev3_motor_get_counts(tgt_port);
        
        return crnt_encR;
    }
    else if(tgt_port == EV3_PORT_A){
        pre_encA  = crnt_encA;
        crnt_encA = ev3_motor_get_counts(tgt_port);
        
        return crnt_encA;
    }
    else{
        printf("An invalid value entered in motor_get_pre_counts.\n");
        return 0;
    }
    
}

extern int32_t motor_get_pre_counts(motor_port_t tgt_port){
    if(tgt_port == EV3_PORT_C){
        return pre_encL;
    }
    else if(tgt_port == EV3_PORT_B){
        return pre_encR;
    }
    else if(tgt_port == EV3_PORT_A){
        return pre_encA;
    }
    else{
        printf("An invalid value entered in motor_get_pre_counts.\n");
        return 0;
    }
}
