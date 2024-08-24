#ifndef _PORT_H
#define _PORT_H

#include "ev3api.h"

/* センサーポートの定義 */
extern const sensor_port_t
    touch_sensor    = EV3_PORT_1,
    color_sensor    = EV3_PORT_2,
    sonar_sensor    = EV3_PORT_3,
    gyro_sensor     = EV3_PORT_4;

/* モーターポートの定義 */
extern const motor_port_t
    arm_motor       = EV3_PORT_A,
    left_motor      = EV3_PORT_C,
    right_motor     = EV3_PORT_B;

/*extern functions*/
extern void set_port();

#endif /* _PORT_H */