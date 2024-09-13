#ifdef __cplusplus
extern "C" {
#endif
#include "ev3api.h"

/* タスク優先度 */
#define MAIN_PRIORITY   (TMIN_APP_TPRI + 1) /* メインタスク */
#define CUNT_PRIORITY   (TMIN_APP_TPRI + 2)
#define BOSS_PRIORITY   (TMIN_APP_TPRI + 4) /* 制御タスク */

/* タスク周期�?�定義 */
// #define LINE_TRACER_PERIOD  (100 * 1000) /* ライントレースタスク:100msec周�? */

#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */


#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void cunt_task(intptr_t exinf);
extern void boss_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
