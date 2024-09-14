#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "ev3api.h"
#include "odometry.h"
#include "port.h"
#include "common.h"
#include "gyak_min.h"
#include "dbNeo.h"
#include "linetrace.h"


// 旋回角度算出処理
int calc_angle(struct coordinate* crnt, struct coordinate* tgt){
    static const float PI = 3.1415926f;
    float tgt_angle = 0.0;
    
    if (crnt->x <= 0.0f){
        tgt->x = tgt->x + abs(crnt->x);
    }else {
        tgt->x = tgt->x - abs(crnt->x);
    }

    // (y座標)
    if (crnt->y <= 0.0f){
        tgt->y = tgt->y + abs(crnt->y);
    }else if(crnt->y > 0.0f){
        tgt->y = tgt->y - abs(crnt->y);
    }else{
        printf("旋回角度算出中に異常発生");
    }

    // 処理2角度計算
    tgt_angle=atan2(tgt->y, tgt->x);
    tgt_angle = tgt_angle * (180.0 / PI);
    printf("(x,y)=(%f,%f) | ",tgt->x, tgt->y);

    return (int)tgt_angle;
}
// 走行距離計算処理
float calc_dist(struct coordinate* crnt, struct coordinate* tgt) {
    double dx = (double)(tgt->x - crnt->x);
    double dy = (double)(tgt->y - crnt->y);

    return (float)sqrt((dx * dx) + (dy * dy));
}

// 旋回処理[暫定]
bool_t proc_turn(int now_angle, int tgt_angle){
    bool_t flag = false;
    if (now_angle < tgt_angle + 5){
        gyak_velocity_control(0.0f, -25.0f);
        printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle, tgt_angle+5);
        flag =false;
    }
    else if (now_angle > tgt_angle - 5){
        gyak_velocity_control(0.0f, 25.0f);
        printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle, tgt_angle-5);
        flag =false;
    }else{
        /* 旋回完了 */
        motor_stop(left_motor);
        motor_stop(right_motor);
        flag =true;
    }
    return flag;
}

// 走行処理[暫定]
bool_t proc_run(float now_dist,float tgt_dist){
    printf("距離情報(現在( %d mm):目標( %d mm )\n",(int)now_dist,(int)tgt_dist);
    bool_t flag = false;
    if (now_dist < tgt_dist - 5.0){
        gyak_velocity_control(50.0f, 0.0f);
        flag = false;
    }
    else if (now_dist > tgt_dist + 5.0){
        gyak_velocity_control(20.0f,0.0f);
        gyak_velocity_control(-30.0f, 0.0f);
        flag = false;
    }else{
        printf("走行完了");
        motor_stop(left_motor);
        motor_stop(right_motor);
        flag = true;
    }

    return flag;
}

// 攻略
extern int hello_neo(){

    static int roop_cnt = 0;
    static bool_t turn_flag = false;
    static bool_t drive_flag = false;
    static bool_t init_flag = false;

    // 定数宣言（目標座標の配列
    /* SIM上の座標を修正。*/
    static float x_pos_target[6]={420.0,520.0,240.0,-220.0,-780.0,-1040.0,-560.0,-260.0,-260.0};
    static float y_pos_target[6]={-140.0,-580.0,-860.0,-760.0,-720.0,-1360.0,-1300.0,-720.0,0.0};
    static struct coordinate crnt_neo = {0.0, 0.0, 0.0}; //自己位置座標
    static struct coordinate tgt_neo  = {0.0, 0.0, 0.0}; //目標位置座標
    static struct coordinate init_neo = {0.0, 0.0, 0.0};
    static int tgt_angl   = 0;
    static float tgt_dist = 0.0;

    /* 現在座標 */
    get_crntCoordinate(&crnt_neo);

    if(roop_cnt < 5){
        /*座標設定*/
        printf("x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",crnt_neo.x, crnt_neo.y, crnt_neo.theta);
        tgt_neo.x = x_pos_target[roop_cnt];
        tgt_neo.y = y_pos_target[roop_cnt];
        
        // 旋回処理
        // 旋回角度計算
        if(init_flag == false){ 
            tgt_angl = calc_angle(&crnt_neo, &tgt_neo);
            init_flag = true;
        }
        // 旋回処理
        else if(init_flag == true && turn_flag==false && drive_flag==false){
            turn_flag = proc_turn(crnt_neo.theta,tgt_angl);

            if(turn_flag==true){
                tgt_dist = calc_dist(&crnt_neo, &tgt_neo);
                get_crntCoordinate(&init_neo); //旋回終了時の座標を取得
            }
        }

        // 走行処理
        if(turn_flag==true && drive_flag==false){
            float crnt_dist = calc_dist(&init_neo, &crnt_neo);
            drive_flag = proc_run(crnt_dist, tgt_dist);
        }

        /* カウント++, リセット処理 */
        if(turn_flag == true && drive_flag == true){
            roop_cnt = roop_cnt + 1;
            turn_flag = false;
            drive_flag = false;
            init_flag = false;
            printf("移動完了(ループ%d回)\n",roop_cnt);
        }

        return 1;
    }
    else{
        return 2;
    }
}

int hello_carry(){

}