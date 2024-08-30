#ifndef _MOTOR_H
#define _MOTOR_H

#include "ev3api.h"
#include "port.h"

extern int32_t encL;
extern int32_t encR;
extern int32_t pre_encL;
extern int32_t pre_encR;

extern int motor_power_L;
extern int motor_power_R;

/* extern functions */
extern void motor_set_power(motor_port_t tgt_port, int power);
extern int  motor_get_power(motor_port_t tgt_port);
extern void motor_reset_counts(motor_port_t tgt_port);
extern int32_t motor_get_counts(motor_port_t tgt_port);
extern int32_t motor_get_pre_counts(motor_port_t tgt_port);

#endif /* _PORT_H */