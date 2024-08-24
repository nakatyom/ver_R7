#ifdef __cplusplus
extern "C" {
#endif
#include "ev3api.h"
#include <stdio.h>

/* タスク優先度 */
#define MAIN_PRIORITY   (TMIN_APP_TPRI + 1) /* メインタスク */
#define ICHI_PRIORITY1  (TMIN_APP_TPRI + 2)
#define ICHI_PRIORITY2  (TMIN_APP_TPRI + 3) 

/* タスク周期の定義 */
// #define LINE_TRACER_PERIOD  (100 * 1000) /* ライントレースタスク:100msec周期 */

#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */


#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void ichi_task1(intptr_t exinf);
extern void ichi_task2(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
