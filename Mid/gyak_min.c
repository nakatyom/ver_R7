#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "gyak_min.h"

const float tgtV_ave = 50.0f; // 目標平均速度[mm/s]
const float tgtR_ave = 45.0f; // 目標平均速度[theta/s]
const cyc_time = 100;         // サイクル周期[ms]
const int array = 11;    // 配列長




/* static functions */


/* external functions */
float calc_TgtVelocity(float tgt_dist){
    static int is_head; // 最初の呼び出しかを判定する
    static int cnt_V;  // 何回目の呼び出しかをカウントする

    /* 並進速度用のパラメータ */
    static float div_dist[11];
    static float tgt_velocity[11];
    float tgt_v = 0;

    /* 最初の一回だけ呼び出される処理 */
    if(0 == is_head){
        float divTime_v;
        float normTime_v;

        /* 到達速度計算 */
        float tgtTime = tgt_dist / tgtV_ave;
        
        /* 各時間における目標距離を配列に格納する */
        for(int i=1; i<=11; i++){
            divTime_v  = (i / 11) * tgtTime; // 分割時間
            normTime_v = divTime_v[i] / tgtTime;     // 正規化時間
            
            /* ジャーク最小化 */
            div_dist[i-1] = tgt_dist * (6*(float)pow(normTime_v,5) - 15*(float)pow(normTime_v,4) + 10*(float)pow(normTime_v,3));
        }

        /* 現在の目標速度を計算 */
        tgt_v = div_dist[cnt_V];

        cnt_V += 1; //カウントアップ

        return tgt_v;
    }
    
    /* 現在の目標速度を計算 */
    tgt_v = ( div_dist[cnt_V] - div_dist[cnt_V-1] ) / cyc_time;

    cnt_V += 1; //カウントアップ

    return tgt_v;
}

float calc_TgtRate(float tgt_theta){
    static int is_head; // 最初の呼び出しかを判定する
    static int cnt_W;  // 何回目の呼び出しかをカウントする

    /* 旋回角度用のパラメータ */
    static float divTime_w[11];
    static float normTime_w[11];
}


// 到達時間計算
// 到達時間を11分割(static 長さ11の配列)
// 正規化時間を計算(static 長さ11の配列)
// 各時間での目標距離を計算
// 各時間での目標速度を計算:(Ln^Ln-1)/delta_t
// return 目標時間

// リセット関数
// 上記のstaticを初期化する
