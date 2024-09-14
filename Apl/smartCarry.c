#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ev3api.h"
#include "odometry.h"
#include "port.h"
#include "common.h"
#include "velocity_control.h"
#include "smartCarry.h"
#include "linetrace.h"


int tgt_angl = 0;
int now_angle = 0;
int tgt_dist = 0;
int now_dist = 0;
float now_x=0.0f;
float now_y=0.0f;
int roop_cnt=0;
bool_t turn_flag = false;
bool_t drive_flag = false;
bool_t init_flag = false; 
int carry_mode=0;
int reflection =0;
rgb_raw_t crnt_rgb_carry;
struct coordinate crnt_carry = {0.0, 0.0, 0.0};//自己位置座標

// 走行距離計算処理
int dist(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt((dx * dx) + (dy * dy));
}

// 旋回角度算出処理
int calc_angle(float tgt_pos_x, float tgt_pos_y){
    static const float PI = 3.14159265358979323846264338327950288;   
    float tgt_angle=0;
    get_crntCoordinate(&crnt_carry);

    // 処理1 原点移動    
    // (x座標)
    //tgt_pos_x = tgt_pos_x - crnt_neo.x;
    //tgt_pos_y = tgt_pos_y - crnt_neo.y;
    
    
    if (crnt_carry.x <= 0.0f){
        tgt_pos_x = tgt_pos_x + abs(crnt_carry.x);
    }else if(crnt_carry.x > 0.0f){
        tgt_pos_x = tgt_pos_x - abs(crnt_carry.x);
    }
    else{
        printf("旋回角度算出中に異常発生");
    }
    // (y座標)
    if (crnt_carry.y <= 0.0f){
        tgt_pos_y = tgt_pos_y + abs(crnt_carry.y);
    }else if(crnt_carry.y > 0.0f){
        tgt_pos_y = tgt_pos_y - abs(crnt_carry.y);
    }else{
        printf("旋回角度算出中に異常発生");
    }

    // 処理2角度計算
    tgt_angle=atan2(tgt_pos_y,tgt_pos_x);
    tgt_angle = tgt_angle * (180 / PI);
    printf("(x,y)=(%f,%f) | ",tgt_pos_x,tgt_pos_y);
    return (int)tgt_angle;

    // 処理2角度計算
    // ロボからみた目的地が第1象限の時。(x,y) (+,+)
    /*
    printf("\n平行移動後の座標(%d,%d)",(int)tgt_pos_x,(int)tgt_pos_y);
    if (tgt_pos_x > 0 && tgt_pos_y >= 0){
        printf("| 第1象限\n");
        if (tgt_pos_y == 0){
            tgt_angle=0;
        }else{
            tgt_angle=atan2(tgt_pos_x,tgt_pos_y);
            tgt_angle = tgt_angle * (180 / PI);
            tgt_angle = tgt_angle; 
        }

    }else if (tgt_pos_x <= 0 && tgt_pos_y > 0){
    // ロボからみた目的地が第2象限の時。(x,y) (-,+)
        printf("| 第2象限\n");
        if (tgt_pos_x == 0){
            tgt_angle=90;
        }else{
            tgt_angle=atan2(tgt_pos_y,tgt_pos_x);
            tgt_angle = tgt_angle * (180 / PI);
            tgt_angle = tgt_angle; 
        }
    }else if (tgt_pos_x < 0 && tgt_pos_y <= 0){
    // ロボからみた目的地が第3象限の時。(x,y) (-,-)
        printf("| 第3象限\n");
        if (tgt_pos_y == 0){
            tgt_angle=-180;
        }else{
            tgt_angle=atan2(tgt_pos_x,tgt_pos_y);
            tgt_angle = tgt_angle * (180 / PI);
            tgt_angle = tgt_angle; 
        }
    }else if (tgt_pos_x >= 0 && tgt_pos_y < 0){
    // ロボからみた目的地が第4象限の時。(x,y) (+,-)
        printf("| 第4象限\n");
        if (tgt_pos_x == 0){
            tgt_angle=-90;
        }else{
            tgt_angle= atan2(tgt_pos_y,tgt_pos_x);
            tgt_angle = tgt_angle * (180 / PI);
            tgt_angle = tgt_angle;
        }
    }
    */
    //tgt_angle = atan((tgt_pos_y-crnt_neo.y)/(tgt_pos_x-crnt_neo.x));
    //printf("(x,y)=(%f,%f) , theta=%f\n 目標位置(100,100)への角度：%f°\n",crnt_neo.x, crnt_neo.y,crnt_neo.theta,tgt_angle);
    //printf("(----------------------------------------------------\n");


}

// 旋回処理[暫定]
bool_t proc_turn(int now_angle, int tgt_angle){
    bool_t flag = false;
    //get_crntCoordinate(&crnt_neo);
    if (now_angle < tgt_angle){
        ev3_motor_set_power(left_motor,  5);
        ev3_motor_set_power(right_motor, -5);
        //printf("処理：分岐１");
        printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle,tgt_angle);
        flag =false;
    }
    else if (now_angle > tgt_angle){
        ev3_motor_set_power(left_motor,  -10);
        ev3_motor_set_power(right_motor, 10);
        //printf("処理：分岐２");
        printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle,tgt_angle);
        flag =false;
    }else{
        printf("旋回完了\n");

        ev3_motor_set_power(left_motor,  0);
        ev3_motor_set_power(right_motor, 0);
        flag =true;
    }
    return flag;
}

// 走行処理[暫定]
bool_t proc_run(float now_dist,float tgt_dist){
    printf("距離情報(現在( %d mm):目標( %d mm )\n",(int)now_dist,(int)tgt_dist);
    bool_t flag = false;
    if (now_dist < tgt_dist){
        ev3_motor_set_power(left_motor,  20);
        ev3_motor_set_power(right_motor, 20);
        flag = false;
    }
    else if (now_dist > tgt_dist){
        ev3_motor_set_power(left_motor,  -2);
        ev3_motor_set_power(right_motor, -2);
        flag = false;
    }else{
        printf("走行完了");
        ev3_motor_set_power(left_motor,  0);
        ev3_motor_set_power(right_motor, 0);
        flag = true;
    }
    return flag;
}


bool_t judge_green(){

    printf("ref = %d | r = %d | g = %d | b = %d\n",reflection, crnt_rgb_carry.r, crnt_rgb_carry.g, crnt_rgb_carry.b);
    if(( crnt_rgb_carry.r >=70 && crnt_rgb_carry.r <=100 ) && ( crnt_rgb_carry.g >=110 && crnt_rgb_carry.g <=170 ) && ( crnt_rgb_carry.b >=135 && crnt_rgb_carry.b <=160 )&& ( reflection >=85 && reflection <=150 )  ){
        printf("_____________________BLUE JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}

bool_t judge_pink(){

    printf("ref = %d | r = %d | g = %d | b = %d\n",reflection, crnt_rgb_carry.r, crnt_rgb_carry.g, crnt_rgb_carry.b);
    if(( crnt_rgb_carry.r >=70 && crnt_rgb_carry.r <=100 ) && ( crnt_rgb_carry.g >=110 && crnt_rgb_carry.g <=170 ) && ( crnt_rgb_carry.b >=135 && crnt_rgb_carry.b <=160 )&& ( reflection >=85 && reflection <=150 )  ){
        printf("_____________________BLUE JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}


// 攻略
int hello_carry(){
    // 定数宣言（目標座標の配列
    /* SIM上の座標を修正。*/
    float x_pos_target[6]={420.0,520.0,240.0,-220.0,-780.0,-1040.0,-560.0,-260.0,-260.0};
    float y_pos_target[6]={-140.0,-580.0,-860.0,-760.0,-720.0,-1360.0,-1300.0,-720.0,0.0};
    
    float velo_rot_target;
    color_sensor_get_rgb_raw(color_sensor,&crnt_rgb_carry);
    reflection = calc_luminance(crnt_rgb_carry);
    if (carry_mode==0){
        get_crntCoordinate(&crnt_carry);
        // 90°旋回
        // ゲッティまち
        if( (int)crnt_carry.theta >= 90){
            carry_mode=1;
            motor_stop(left_motor);
            motor_stop(right_motor);
        }

    }else if(carry_mode == 1){
        // 緑を検知するまで直進
        if (judge_green() == true){
            motor_stop(left_motor);
            motor_stop(right_motor);
            carry_mode=2;
        }else{
            // 直進
            mid_velocity_control(60.0f, 0.0f);
        }
    }else if(carry_mode == 2){
        // 緑でなくなるまで旋回
        if (judge_green() == false){
            carry_mode=3;
            motor_stop(left_motor);
            motor_stop(right_motor);
        }else{
            mid_velocity_control(0.0f, 60.0f);
        }
    }else if(carry_mode=3){
        //緑に合わせて、定数を更新
        velo_rot_target = mid_PID_line_pos(55.0f, (float)reflection,50);
        mid_velocity_control(50.0f,velo_rot_target);
        //ピンクを検知するまで進む。
        if (judge_pink() == true){
            carry_mode=4;
            motor_stop(left_motor);
            motor_stop(right_motor);
        }
    }else if(carry_mode==4){
        // リセットを追加。
        get_crntCoordinate(&crnt_carry);
        if(roop_cnt <= 5){
            now_angle = (int)(crnt_carry.theta);
            printf("x=%f, y=%f, theta=%f° , 変換後=%f° | ",crnt_carry.x, crnt_carry.y, crnt_carry.theta ,trans_gDeg(crnt_carry.theta));
            // 旋回処理
            if (init_flag == false){ 
                tgt_angl = calc_angle(x_pos_target[roop_cnt],y_pos_target[roop_cnt]);
                init_flag = true;
            }else if (init_flag == true && turn_flag==false && drive_flag==false){
                turn_flag=proc_turn(now_angle,tgt_angl);
                if(turn_flag==true){
                    tgt_dist = dist(crnt_carry.x,crnt_carry.y,x_pos_target[roop_cnt],y_pos_target[roop_cnt]);
                    now_x = crnt_carry.x;
                    now_y = crnt_carry.y;
                }
            }
            // 走行処理
            if (turn_flag==true && drive_flag==false){
                now_dist = dist(crnt_carry.x,crnt_carry.y,now_x,now_y);
                //tgt_dist = (int)dist(crnt_carry.x,crnt_carry.y,x_pos_target[roop_cnt],y_pos_target[roop_cnt]);
                drive_flag = proc_run(now_dist,tgt_dist);

            }
            if (turn_flag==true && drive_flag==true){
                roop_cnt = roop_cnt + 1;
                turn_flag = false;
                drive_flag = false;
                init_flag = false;
                printf("移動完了(ループ%d回)\n",roop_cnt);
                printf("現在座標（%f,%f）\n",crnt_carry.x,crnt_carry.y);
                printf("目標座標（%f,%f）\n",x_pos_target[roop_cnt],y_pos_target[roop_cnt]);
            }
            return 3;
        }else{
            printf("SmartCarry完了！！！！");
            return 4;
        }
    }

}