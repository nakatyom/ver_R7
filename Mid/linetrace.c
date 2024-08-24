#include "ev3api.h"
#include "port.h"
#include "linetrace.h"

const int lr_sw = 1; // L_COURSE:1, R_COURSE:-1
const float KP = 1.0;
const float KD = 1.0;
const u_int8_t target = 100;
u_int8_t pre_err = 0;
int BASE = 35;
float motor_compensater = 0.92;

void linetrace(){

    /* 反射強度の取得 */
    u_int8_t crnt = ev3_color_sensor_get_reflect(color_sensor);

    /* PID計算 */
    u_int8_t err = target - crnt;
    u_int8_t out = (u_int8_t)( KP * err + KD * (err-pre_err) );
    pre_err = err;

    /* パワー計算 */
    int left_power  = BASE + lr_sw * out;
    int right_power = BASE - lr_sw * out;

    /* モータ出力 */
    left_power *= (int)(motor_compensater * left_power);
    ev3_motor_set_power(left_motor, left_power);
    ev3_motor_set_power(right_motor, right_power);

}