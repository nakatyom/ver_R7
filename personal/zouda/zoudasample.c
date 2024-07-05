/*zoudazoudazoudazouda4645*/

#include "ev3api.h"
#include <stusio.h>

static void motor_run(int16_t);

ev3_motor_config(EV3_PORT_B, MEDIUM_MOTOR)
ev3_motor_config(EV3_PORT_C, MEDIUM_MOTOR)

ev3_motor_set_power(EV3_PORT_B, 10)
ev3_motor_set_power(EV3_PORT_C, 10)

/*
void only_run_task(intptr_t unused)
{
    motor_run(val);
}

static void motor_run(void)
{
    ev3_motor_set_power(EV3_PORT_B, 10)
    ev3_motor_set_power(EV3_PORT_C, 10)
    
}
*/