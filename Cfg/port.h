#ifndef _PORT_H
#define _PORT_H

#include "ev3api.h"

extern const sensor_port_t touch_sensor;
extern const sensor_port_t color_sensor;
extern const sensor_port_t sonar_sensor;
extern const sensor_port_t gyro_sensor;

extern const motor_port_t arm_motor;
extern const motor_port_t left_motor;
extern const motor_port_t right_motor;

extern void set_portCfg(void);


#endif /* _PORT_H */