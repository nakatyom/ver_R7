#ifndef _MOTOR_H
#define _MOTOR_H

#include "ev3api.h"
#include "port.h"

/* extern functions */
extern int32_t motor_get_counts(motor_port_t tgt_port);
extern int32_t motor_get_pre_counts(motor_port_t tgt_port);
extern void motor_reset_counts(motor_port_t tgt_port);
extern void motor_set_power(motor_port_t tgt_port, int power);
extern int  motor_get_power(motor_port_t tgt_port);
extern int  motor_get_pre_power(motor_port_t tgt_port);
extern void motor_stop(motor_port_t tgt_port);

#endif /* _PORT_H */