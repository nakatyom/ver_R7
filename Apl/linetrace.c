#include <stdio.h>

#include "ev3api.h"
#include "port.h"
#include "velocity_control.h"
#include "linetrace.h"
#include "odometry.h"

float mid_PID_line_pos(float tag, float maj,int pwr){ 
    
    printf("ref = %f | ",maj);

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

u_int8_t reflection =0;
rgb_raw_t crnt_rgb_line;
struct coordinate crnt_line = {0.0, 0.0, 0.0};//自己位置座標

bool_t judge_blue(){
    //rgb_raw_t crnt_rgb_line;
    //u_int8_t reflection = color_sensor_get_reflect(color_sensor);
    //color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_line);
    printf("ref = %d | r = %d | g = %d | b = %d\n",reflection, crnt_rgb_line.r, crnt_rgb_line.g, crnt_rgb_line.b);
    if(( crnt_rgb_line.r >=70 && crnt_rgb_line.r <=100 ) && ( crnt_rgb_line.g >=110 && crnt_rgb_line.g <=170 ) && ( crnt_rgb_line.b >=135 && crnt_rgb_line.b <=160 )&& ( reflection >=85 && reflection <=150 )  ){
        printf("_____________________BLUE JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}

bool_t judge_black(){
    
    //u_int8_t reflection = color_sensor_get_reflect(color_sensor);
    //ev3_color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_line);
    printf("ref = %d | r = %d | g = %d | b = %d\n",reflection, crnt_rgb_line.r, crnt_rgb_line.g, crnt_rgb_line.b);
    if(( crnt_rgb_line.r >=80 && crnt_rgb_line.r <=90 ) && ( crnt_rgb_line.g >=95 && crnt_rgb_line.g <=105 ) && ( crnt_rgb_line.b >=104 && crnt_rgb_line.b <=114 )&& ( reflection >=70 && reflection <=80 )  ){
        printf("_____________________BLACK JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}
bool_t kotesaki = false;
int cnt =0;
extern int linetrace(){
    float velo_rot_target;
    get_crntCoordinate(&crnt_line);
    reflection = color_sensor_get_reflect(color_sensor);

    if (divion == 0){
        printf("x=%f, y=%f, theta=%f | ",crnt_line.x, crnt_line.y, crnt_line.theta);
        if((crnt_line.x >=2750 && crnt_line.y >= -300) || (crnt_line.x >=2750 && crnt_line.y <= -1800)){
            printf("判定1 \n");
            velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,50);
            mid_velocity_control(50.0f, -velo_rot_target);
            if (crnt_line.x >=2750 && crnt_line.y <= -1800 && kotesaki==false){
                kotesaki=true;
            }
        }
        else{ 
            printf("判定2 \n");
            velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,90);
            mid_velocity_control(90.0f, -velo_rot_target);
            if (kotesaki == true){   
                printf("小手先のカラーセンサ");
                color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_line);
                if(judge_blue()== true){
                    printf("黒検知平行：%d\n",cnt);
                    divion = 1;
                }
            }
        }
        return 0;
    }else if(divion == 1){//RGB==BLACK
        cnt + cnt + 1;
        if (cnt < 25){
            motor_stop(left_motor);
            motor_stop(right_motor);
            printf("STOPカウント：%d",cnt);
        }
        else{
            printf("判定3 \n");
            velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,50);
            mid_velocity_control(50.0f, -velo_rot_target);
            color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_line);
            if(judge_black()==true){
                divion = 2;
            }
        }
        return 0;
    }else{
        motor_stop(left_motor);
        motor_stop(right_motor);
        printf("FINISH LINETRACE\n");
        return 1;
    }
}
