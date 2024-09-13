#include <stdio.h>

#include "ev3api.h"
#include "port.h"
#include "test_sensor.h"

void test_sensor(void){
    int16_t l_enc = motor_get_counts(left_motor);
    int16_t r_enc = motor_get_counts(right_motor);

    int16_t g_angle = gyro_sensor_get_angle(gyro_sensor);
    
    uint8_t ref = color_sensor_get_reflect(color_sensor);
    rgb_raw_t crnt;
    color_sensor_get_rgb_raw(color_sensor, &crnt);

    printf("left_enc: %d, ", l_enc);
    printf("right_enc: %d,  ", r_enc);
    printf("g_angle: %d,  ", g_angle);
    printf("ref: %d, ", ref);
    printf("rgb: %d, %d, %d\n",crnt.r, crnt.g, crnt.b);


}