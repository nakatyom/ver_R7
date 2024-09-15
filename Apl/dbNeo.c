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
    if (now_angle < tgt_angle){
        gyak_velocity_control(0.0f, -25.0f);
        printf("比較角度(現在( %d° ):目標( %d° )\n",now_angle, tgt_angle+5);
        flag =false;
    }
    else if (now_angle > tgt_angle){
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

int reflection_ = 0;
rgb_raw_t color_;


int calc_luminance_(rgb_raw_t color) {
    // 加重平均で明度を計算し、int型に変換
    int luminance = (int)(0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
    // luminance = (luminance * 100) / 255; //百分率計算

    return luminance;
}
bool_t judge_blue_(){
    if(( color_.r >=15 && color_.r <=100 ) && ( color_.g >=50 && color_.g <=130 ) && ( color_.b >=120 && color_.b <=255 )&& ( reflection_ >=25 && reflection_ <=100 )  ){
        printf("_____________________BLUE JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}
bool_t judge_black_(){
    if(( color_.r >=10 && color_.r <=90 ) && ( color_.g >=10 && color_.g <=110 ) && ( color_.b >=10 && color_.b <=110 )&& ( reflection_ >=10 && reflection_ <=80 )){
        printf("_____________________BLACK JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}
bool_t judge_red_(){
    if(( color_.r >=10 && color_.r <=90 ) && ( color_.g >=10 && color_.g <=110 ) && ( color_.b >=10 && color_.b <=110 )&& ( reflection_ >=10 && reflection_ <=80 )){
        printf("_____________________RED JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}
bool_t judge_yellow_(){
    if(( color_.r >=10 && color_.r <=90 ) && ( color_.g >=10 && color_.g <=110 ) && ( color_.b >=10 && color_.b <=110 )&& ( reflection_ >=10 && reflection_ <=80 )){
        printf("_____________________YELLOW JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}
bool_t judge_pink_(){
    if(( color_.r >=136 && color_.r <=156 ) && ( color_.g >=78 && color_.g <=98 ) && ( color_.b >=107 && color_.b <=127 )&& ( reflection_ >=10 && reflection_ <=80 )){
        printf("_____________________PINK JUDGE_____________________\n");
        return true;
    }
    else{
        return false;
    }
}

float mid_PID_line_pos_carry(float tag, float maj,int pwr){ 
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


// 攻略
/* ダブルループ */
float last_angle_neo = 0;
float last_angle_dm = 0;
float last_angle_carry = 0;

extern int hello_neo(){
    static int roop_cnt = 0;
    static bool_t turn_flag = false;
    static bool_t drive_flag = false;
    static bool_t init_flag = false;

    // 定数宣言（目標座標の配列
    /* SIM上の座標を修正。*/
    #define NEO_LOOP 10
    static float x_pos_target[NEO_LOOP]={ 420.0, 520.0, 240.0,-220.0,-780.0,- 560.0,-260.0,-300.0,100.0, 100.0};
    static float y_pos_target[NEO_LOOP]={-140.0,-580.0,-860.0,-760.0,-720.0,-1300.0,-900.0,-400.0,  0.0,   0.0};
    static struct coordinate crnt_neo = {0.0, 0.0, 0.0}; //自己位置座標
    static struct coordinate tgt_neo  = {0.0, 0.0, 0.0}; //目標位置座標
    static struct coordinate init_neo = {0.0, 0.0, 0.0};
    static int tgt_angl   = 0;
    static float tgt_dist = 0.0;

    /* 現在座標 */
    get_crntCoordinate(&crnt_neo);

    if(roop_cnt < NEO_LOOP){
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

            if(roop_cnt == NEO_LOOP-2 || roop_cnt == NEO_LOOP-1){ //ダブルループ脱出orライントレース調整
                color_sensor_get_rgb_raw(color_sensor,&color_);
                reflection_ = calc_luminance(color_);

                if(true == judge_black_()){ //黒判定
                    crnt_dist = tgt_dist;
                }
            }

            drive_flag = proc_run(crnt_dist, tgt_dist);
        }

        /* カウント++, リセット処理 */
        if(turn_flag == true && drive_flag == true){
            roop_cnt = roop_cnt + 1;
            turn_flag = false;
            drive_flag = false;
            init_flag = false;
            printf("移動完了(ループ%d回)\n",roop_cnt);
            printf("現在位置：x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",crnt_neo.x, crnt_neo.y, crnt_neo.theta);
            printf("目標位置：x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",tgt_neo.x, tgt_neo.y, tgt_neo.theta);
        }

        return 1;
    }
    else if(roop_cnt < NEO_LOOP + 1){
        color_sensor_get_rgb_raw(color_sensor,&color_);
        reflection_ = calc_luminance(color_);

        if(true == judge_blue_()){ //青判定
            roop_cnt += 1;
        }
        else {
            float velo_rot_target = mid_PID_line_pos(80.0f, (float)reflection_,50);
            mid_velocity_control(50.0f, -velo_rot_target);
        }

    }
    else{
        reset_Coordinate();
        last_angle_neo = (int)crnt_neo.theta; //ロボットの最終向きを記憶
        return 2;
    }
}

/* デブリリムーバル */
int hello_dmrm(){
    static int roop_cnt_dm = 0;
    static bool_t turn_flag_dm = false;
    static bool_t drive_flag_dm = false;
    static bool_t init_flag_dm = false;

    // 定数宣言（目標座標の配列
    /* SIM上の座標を修正。*/
    #define DM_LOOP 6
    static float x_pos_target_dm[DM_LOOP]={950.0, 970.0, 1015.0, 1015.0, 1015.0, 1100.0};
    static float y_pos_target_dm[DM_LOOP]={  0.0,   0.0,  -35.0, -850.0, -880.0, -950.0};
    static struct coordinate crnt_dm = {0.0, 0.0, 0.0}; //自己位置座標
    static struct coordinate tgt_dm  = {0.0, 0.0, 0.0}; //目標位置座標
    static struct coordinate init_dm = {0.0, 0.0, 0.0};
    static int tgt_angl_dm   = 0;
    static float tgt_dist_dm = 0.0;

    /* 現在座標 */
    get_crntCoordinate(&crnt_dm);

    if(roop_cnt_dm < DM_LOOP){
        /*座標設定*/
        printf("x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",crnt_dm.x, crnt_dm.y, crnt_dm.theta);
        tgt_dm.x = x_pos_target_dm[roop_cnt_dm];
        tgt_dm.y = y_pos_target_dm[roop_cnt_dm];

        // 旋回処理
        // 旋回角度計算
        if(init_flag_dm == false){
            crnt_dm.theta = last_angle_neo; 
            tgt_angl_dm = calc_angle(&crnt_dm, &tgt_dm);
            init_flag_dm = true;
        }
        else if(init_flag_dm == true && turn_flag_dm == false && drive_flag_dm == false){
            turn_flag_dm = proc_turn(crnt_dm.theta, tgt_angl_dm);     
            if(turn_flag_dm == true){
                tgt_dist_dm = calc_dist(&crnt_dm, &tgt_dm);
                get_crntCoordinate(&init_dm); //旋回終了時の座標を取得
            }
        }
        
        // 走行処理     
        if(turn_flag_dm == true && drive_flag_dm == false){
            float crnt_dist_dm = calc_dist(&init_dm, &crnt_dm);
            
            if(roop_cnt_dm == 1 || roop_cnt_dm == 3){ //赤円or黄円手前
                color_sensor_get_rgb_raw(color_sensor,&color_);
                reflection_ = calc_luminance(color_);

                if(true == judge_red_()){ //赤円判定
                    crnt_dist_dm = tgt_dist_dm;
                }
                else if(true == judge_yellow_()){//黄円判定
                    crnt_dist_dm = tgt_dist_dm;
                }
            }

            drive_flag_dm = proc_run(crnt_dist_dm, tgt_dist_dm);
        }
        
        /* カウント++, リセット処理 */
        if(turn_flag_dm == true && drive_flag_dm == true){
            roop_cnt_dm = roop_cnt_dm + 1;
            turn_flag_dm = false;
            drive_flag_dm = false;
            init_flag_dm = false;
            printf("移動完了(ループ%d回)\n",roop_cnt_dm);
            printf("現在位置：x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",crnt_dm.x, crnt_dm.y, crnt_dm.theta);
            printf("目標位置：x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",tgt_dm.x, tgt_dm.y, tgt_dm.theta);
        }


        return 1;
    }
    else{
        last_angle_dm = (int)tgt_dm.theta; //ロボットの最終向きを記憶
        reset_Coordinate();
        return 2;
    }
}


/* スマートキャリー */
int hello_carry(){
    static int roop_cnt_carry = 0;
    static bool_t turn_flag_carry = false;
    static bool_t drive_flag_carry = false;
    static bool_t init_flag_carry = false;

    // 定数宣言（目標座標の配列
    /* SIM上の座標を修正。*/
    static float x_pos_target_carry[1]={-382.0,  -116.0,-138.0, 386.0, 386.0};
    static float y_pos_target_carry[1]={   0.0, -1013.0,-897.0,-400.0,-127.0};
    static struct coordinate crnt_carry = {0.0, 0.0, 0.0}; //自己位置座標
    static struct coordinate tgt_carry  = {0.0, 0.0, 0.0}; //目標位置座標
    static struct coordinate init_carry = {0.0, 0.0, 0.0};
    static int tgt_angl_carry   = 0;
    static float tgt_dist_carry = 0.0;

    static int carry_mode = 0;
    rgb_raw_t color_;

    if (carry_mode == 0){

        color_sensor_get_rgb_raw(color_sensor,&color_);
        reflection_ = calc_luminance(color_);
        float velo_rot_target = mid_PID_line_pos_carry(60.0f, (float)reflection_,50);
        mid_velocity_control(50.0f, -velo_rot_target);

        if(true == judge_pink_()){ //ピンク判定

            motor_stop(left_motor);
            motor_stop(right_motor);
            reset_Coordinate();
            carry_mode = 1;
        }

    }else if (carry_mode == 1){
        /* 現在座標 */
        get_crntCoordinate(&crnt_carry);

        if(roop_cnt_carry < 8){ // 0 - 8
            /*座標設定*/
            printf("x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",crnt_carry.x, crnt_carry.y, crnt_carry.theta);
            tgt_carry.x = x_pos_target_carry[roop_cnt_carry];
            tgt_carry.y = y_pos_target_carry[roop_cnt_carry];
        }
        if(roop_cnt_carry == 0 || ){
            // 旋回処理
            // 旋回角度計算
            if(init_flag_carry == false){
                crnt_carry.theta = last_angle_dm; 
                tgt_angl_carry  = calc_angle(&crnt_carry, &tgt_carry);
                init_flag_carry = true;
            }
        }
        // 旋回処理
        else if(init_flag_carry == true && turn_flag_carry == false && drive_flag_carry == false){
            turn_flag_carry = proc_turn(crnt_carry.theta, tgt_angl_carry);

            if(turn_flag_carry == true){
                tgt_dist_carry = calc_dist(&crnt_carry, &tgt_carry);
                get_crntCoordinate(&init_carry); //旋回終了時の座標を取得
            }
        }

        // 走行処理
        if(turn_flag_carry == true && drive_flag_carry == false){
            float crnt_dist_carry = calc_dist(&init_carry, &crnt_carry);
            drive_flag_carry = proc_run(crnt_dist_carry, tgt_dist_carry);
        }

        /* カウント++, リセット処理 */
        if(turn_flag_carry == true && drive_flag_carry == true){
            roop_cnt_carry = roop_cnt_carry + 1;
            turn_flag_carry = false;
            drive_flag_carry = false;
            init_flag_carry = false;
            printf("移動完了(ループ%d回)\n",roop_cnt_carry);
            printf("現在位置：x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",crnt_carry.x, crnt_carry.y, crnt_carry.theta);
            printf("目標位置：x=%8.4f[mm], y=%8.4f[mm], theta=%8.4f°\n",tgt_carry.x, tgt_carry.y, tgt_carry.theta);
        }

        return 1;
    
    }else{
        last_angle_carry = (int)tgt_carry.theta;//ロボットの最終向きを記憶
        return 2;
    }
}