#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"

/* タスク優先度 */
#define MAIN_PRIORITY   (TMIN_APP_TPRI + 1) /* メインタスク */
#define LOG_PRIORITY    (TMIN_APP_TPRI + 2) /* ログ タスク */

/* タスク周期の定義 */


#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void log_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
