#include "ev3api.h"
#include <stdio.h>
#include "app.h"
#include "port_settings.h"

#define BASE_SPEED 50  // 基本速度
#define BLUE_REF 39
#define BLACK_REF 15
#define KP 1.1         // 比例ゲイン
#define KI 0.1         // 積分ゲイン
#define KD 0.02        // 微分ゲイン

int reflection;
int power_left, power_right;
int error, last_error = 0, integral = 0;
int correction;
int target ;  // 目標値

// 値をクリップする関数
int clip(int value, int min, int max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

uint32_t cnt=0;
rgb_raw_t rgb_val;

void mid_linetrace_pid(intptr_t unused){

    // 反射光の強さを取得
    reflection = ev3_color_sensor_get_reflect(color_sensor);
    ev3_color_sensor_get_rgb_raw(color_sensor,&rgb_val);

    
    if (rgb_val.r <= 20 and rgb_val.g<= 48 && rgb_val.b <= 85){
        target = BLACK_REF;
    }else{
        target = BLUE_REF;
    }
    
    
    // デバックコード
    if (ev3_touch_sensor_is_pressed(touch_sensor) && (cnt % 1000000 == 0)) {
        //target += 1;  // 目標値を増加
        if (target > 100) {
            target = 0;  // 目標値をリセット
        }
    }else{
        if (cnt%100000000==0){
            printf("colorval:%d | Target %d | Color(R,G,B)=(%d,%d,%d)\n",reflection,target,rgb_val.r,rgb_val.g,rgb_val.b);
        }
    }
    if (cnt>=6500000000){
        cnt=0;
    }

    // エラー計算
    error = target - reflection;
    integral += error;
    correction = KP * error + KD * (error - last_error); //+ KI * integral ;

    // 左右のモーターのパワーを設定
    power_left = BASE_SPEED - correction;
    power_right = BASE_SPEED + correction;

    // パワーを-100～100の範囲にクリップ
    power_left = clip(power_left, -100, 100);
    power_right = clip(power_right, -100, 100);

    ev3_motor_set_power(left_motor, power_left);
    ev3_motor_set_power(right_motor, power_right);

    // 前回のエラーを更新
    last_error = error;
}

