#include <stdio.h>

#include "ev3api.h"
#include "port.h"
#include "velocity_control.h"
#include "linetrace.h"
#include "odometry.h"


float mid_PID_line_pos(float tag, float maj,int pwr){ 

    float kp = 0.2f;
    float ki = 0.02f;
    float kd = 0.10f;
    
    /* power 90 の時。Straight */
    if (pwr==90){
        kp = 0.2f;
        ki = 0.02f;
        kd = 0.10f;
    }else{
    /* power 50 の時。Cave */
        kp = 0.30f;
        ki = 0.04f;
        kd = 0.13f;
    }


    static float intg;
    static float err_pre;
    static float err;
     
    err_pre = err;
    err = tag - maj;
    intg += err;

    if (intg > 1000.0f)    intg = 1000.0f;
    if (intg < -1000.0f)   intg = -1000.0f;

    return ((err * kp) + (intg * ki) + ((err - err_pre) * kd));
}

int divion = 0;
int finish = 0;
rgb_raw_t crnt_rgb_line;
struct coordinate crnt_line = {0.0, 0.0, 0.0};//自己位置座標


extern bool_t judge_blue(){
    int reflection = ev3_color_sensor_get_reflect(color_sensor);
    if(( crnt_rgb_line.r >=10 && crnt_rgb_line.r <=20 ) && ( crnt_rgb_line.g >=42 && crnt_rgb_line.g <=52 ) && ( crnt_rgb_line.b >=80 && crnt_rgb_line.b <=90 )&& ( reflection >=30 && reflection <=40 )  ){
        return true;
    }
    else{
        return false;
    }
}

extern bool_t judge_black(){
    int reflection = ev3_color_sensor_get_reflect(color_sensor);
    if(( crnt_rgb_line.r >=4 && crnt_rgb_line.r <=13 ) && ( crnt_rgb_line.g >=5 && crnt_rgb_line.g <=15 ) && ( crnt_rgb_line.b >=7 && crnt_rgb_line.b <=17 )&& ( reflection >=3 && reflection <=14 )  ){
        return true;
    }
    else{
        return false;
    }
}

int linetrace(void){
    get_crntCoordinate(&crnt_line);
    // BLUE検知まで走行する処理。
    int reflection = ev3_color_sensor_get_reflect(color_sensor);
    float velo_rot_target;
    if (divion == 0){
        if(judge_blue() == true){divion = 1;}// RGB==BLUE
        if((crnt_line.x >=2750 && crnt_line.y >= -220) || (crnt_line.x >=2750 && crnt_line.y <= -1800)){ //コーナーエリア
            velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,50);
            mid_velocity_control(50.0f, -velo_rot_target);
        }else{ //ストレートエリア
            velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,90);
            mid_velocity_control(90.0f, -velo_rot_target);
        }
        return 0;
    }else if(divion = 1){//RGB==BLACK
        if(judge_black==true){divion = 2;}
        mid_velocity_control(50.0f, -velo_rot_target);
        return 0;
    }else{
        motor_stop(left_motor);
        motor_stop(right_motor);
        printf("FINISH LINETRACE\n");
        return 1;
    }
}
