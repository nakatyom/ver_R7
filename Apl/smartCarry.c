#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ev3api.h"
#include "odometry.h"
#include "smartCarry.h"
#include "port.h"



// 走行距離計算処理
extern float dist(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}


// 旋回角度算出処理
extern float calc_angle(float tgt_pos_x,float tgt_pos_y){
    static const float PI = 3.14159265358979323846264338327950288;   
    float tgt_angle=0;
    struct coordinate crnt = {0.0, 0.0, 0.0};
    get_crntCoordinate(&crnt);
    //printf("x=%f, y=%f, theta=%f\n",crnt.x, crnt.y, crnt.theta);
    // arctan2 関数用の下処理。(x座標)
    if (crnt.x <= 0.0f){
        tgt_pos_x = tgt_pos_x + crnt.x;
    }else if(crnt.x > 0.0f){
        tgt_pos_x = tgt_pos_x - crnt.x;
    }
    else{
        printf("旋回角度算出中に異常発生");
    }
    // arctan2 関数用の下処理。(y座標)
    if (crnt.y <= 0.0f){
        tgt_pos_y = tgt_pos_y + crnt.y;
    }else if(crnt.y > 0.0f){
        tgt_pos_y = tgt_pos_y - crnt.y;
    }else{
        printf("旋回角度算出中に異常発生");
    }
    
    tgt_angle = atan2(tgt_pos_y,tgt_pos_x);
    
    tgt_angle = tgt_angle * (180 / PI);

    //printf("(x,y)=(%f,%f) , theta=%f\n 目標位置(100,100)への角度：%f°\n",crnt.x, crnt.y,crnt.theta,tgt_angle);
    //printf("(----------------------------------------------------\n");

    
    return tgt_angle;
}


// 攻略
bool_t turn_flag = false;
bool_t drive_flag = false; 
int tgt_angl=0;
int now_angle = 0;
int tgt_dist = 0;
int now_dist = 0;
float now_x=0.0f;
float now_y=0.0f;

void hello_neo(){
    // 定数宣言（目標座標の配列）
    float x_pos_target[6]={420.0,580.0,860.0,960.0,720.0,1360,1300,720.0,0};
    float y_pos_target[6]={140.0,520.0,240.0,-440.0,-260.0,-780.0,-1040.0,-560.0,-260.0};
    struct coordinate crnt = {0.0, 0.0, 0.0};//自己位置座標
    get_crntCoordinate(&crnt);
    // 変数宣言
    tgt_angl = (int)calc_angle(y_pos_target[0],x_pos_target[0]);
    now_angle = (int)crnt.theta;
    
    // 旋回処理
    if (turn_flag==false && drive_flag==false){
        if (now_angle < tgt_angl){
            ev3_motor_set_power(left_motor,  8);
            ev3_motor_set_power(right_motor, -8);
            //printf("処理：分岐１");
            printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle,tgt_angl);
        }
        else if (now_angle > tgt_angl){
            ev3_motor_set_power(left_motor,  -8);
            ev3_motor_set_power(right_motor, 8);
            //printf("処理：分岐２");
            printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle,tgt_angl);
        }else{
            printf("旋回完了\n");
            get_crntCoordinate(&crnt);
            //turn_flag=true;
            ev3_motor_set_power(left_motor,  0);
            ev3_motor_set_power(right_motor, 0);
            tgt_dist = (int)dist(crnt.x,crnt.y,x_pos_target[0],y_pos_target[0]);
            now_x = crnt.x;
            now_y = crnt.y;
        }
    }
    // 走行処理
    if (turn_flag==true && drive_flag==false){
        now_dist = (int)dist(crnt.x,crnt.y,now_x,now_y);
        printf("now_dist:%d , tgt_dist:%d\n",now_dist,tgt_dist);
        if (now_dist < tgt_dist){
            ev3_motor_set_power(left_motor,  8);
            ev3_motor_set_power(right_motor, 8);
            //printf("処理：分岐１");
            //printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle,angle);
        }
        else if (now_dist > tgt_dist){
            ev3_motor_set_power(left_motor,  -2);
            ev3_motor_set_power(right_motor, -2);
            //printf("処理：分岐２");
            //printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle,angle);
        }else{
            printf("走行完了");
            drive_flag=true;
            ev3_motor_set_power(left_motor,  0);
            ev3_motor_set_power(right_motor, 0);
        }
    }
    /*
    if (turn_flag==true && drive_flag==true){
        printf("移動完了(ループ1回)\n");
    }*/

}

