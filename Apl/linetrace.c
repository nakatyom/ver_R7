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
rgb_raw_t crnt_rgb_line;
u_int8_t reflection =0;
struct coordinate crnt_line = {0.0, 0.0, 0.0};//自己位置座標

extern bool_t judge_blue(){
    //rgb_raw_t crnt_rgb_line;
    //u_int8_t reflection = color_sensor_get_reflect(color_sensor);
    //ev3_color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_line);
    printf("ref = %d | r = %d | g = %d | b = %d\n",reflection, crnt_rgb_line.r, crnt_rgb_line.g, crnt_rgb_line.b);
    if(( crnt_rgb_line.r >=80 && crnt_rgb_line.r <=90 ) && ( crnt_rgb_line.g >=110 && crnt_rgb_line.g <=225 ) && ( crnt_rgb_line.b >=140 && crnt_rgb_line.b <=150 )&& ( reflection >=85 && reflection <=150 )  ){
        printf("_____________________BLUE JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}

extern bool_t judge_black(){
    
    //u_int8_t reflection = color_sensor_get_reflect(color_sensor);
    //ev3_color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_line);
    printf("ref = %d | r = %d | g = %d | b = %d\n",reflection, crnt_rgb_line.r, crnt_rgb_line.g, crnt_rgb_line.b);
    if(( crnt_rgb_line.r >=70 && crnt_rgb_line.r <=80 ) && ( crnt_rgb_line.g >=80 && crnt_rgb_line.g <=90 ) && ( crnt_rgb_line.b >=95 && crnt_rgb_line.b <=100 )&& ( reflection >=68 && reflection <=77 )  ){
        printf("_____________________BLACK JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}

int linetrace(void){
    float velo_rot_target;
    color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_line);
    reflection = color_sensor_get_reflect(color_sensor);
    get_crntCoordinate(&crnt_line);
    printf("x=%f, y=%f, theta=%f | ",crnt_line.x, crnt_line.y, crnt_line.theta);
    // BLUE検知まで走行する処理。


    
    if (divion == 0){
        if(judge_blue() == true){divion = 1;}// RGB==BLUE
        if((crnt_line.x >=2750 && crnt_line.y >= -300) || (crnt_line.x >=2750 && crnt_line.y <= -1800)){ //コーナーエリア
            printf("判定1 \n");
            velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,50);
            mid_velocity_control(50.0f, -velo_rot_target);
        }else{ //ストレートエリア
            printf("判定2 \n");
            velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,90);
            mid_velocity_control(90.0f, -velo_rot_target);
        }
        return 0;
    }else if(divion == 1){//RGB==BLACK
        if(judge_black==true){divion = 2;}
        printf("判定3 \n");
        velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,50);
        mid_velocity_control(50.0f, -velo_rot_target);
        return 0;
    }else{
        motor_stop(left_motor);
        motor_stop(right_motor);
        printf("FINISH LINETRACE\n");
        return 1;
    }
}
