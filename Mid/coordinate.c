#include "coordinate.h"

extern void ecoor_update(); //エッジ座標更新
extern void ncoor_update(); //現在座標更新
extern void tcoor_update(); //ターゲット座標更新

struct coor{
    int x;
    int y;
}

extern coor ecoor_get(); //エッジ座標取得
extern coor ncoor_get(); //現在座標取得
extern coor tcoor_get(); //ターゲット座標取得

