#include <stdio.h>

#include "ev3api.h"
#include "common.h"
#include "gyak_min.h"

float tgtV_ave = 50.0; //　目標平均速度[mm/s]


/* static functions */


/* external functions */
float get_tgtV(struct coordinate* tgt_coordinate, struct coordinate* crnt_coordinate){


}

void reset_tgtV(){

}

// 目標座標、現在座標→距離、角度
// 到達時間計算
// 到達時間を50分割(static 長さ51の配列)
// 正規化時間を計算(static 長さ51の配列)
// 各時間での目標距離を計算
// 各時間での目標速度を計算:(Ln^Ln-1)/delta_t
// return 目標時間

// リセット関数
// 上記のstaticを初期化する
