/* Note */
// These APIs update battery infomations 1[time/second].

#include "ev3api.h"
#include "app.h"
#include <stdio.h>

#include "battery.h"


/* define */
#define V_MAX 5000
#define V_MIN 0
#define C_MAX 1000
#define C_MIN 0

/* external functions */

int get_batV(void){
    int volt = 0;

    volt = ev3_battery_voltage_mV();

    if(volt > V_MAX || volt =< V_MIN){
        printf("voltage value is out of range.");
        return -1;
    }

    return volt;
}

int get_batC(void){
    int current = 0;

    current = ev3_battery_current_mV();

    if(current > C_MAX || current =< C_MIN){
        printf("current value is out of range.");
        return -1;
    }

    return current;
}