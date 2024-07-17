#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* enum */
extern enum {
    BATTERY,        // measure_battery_val (int)
    BUTTON,         // measure_button_state (bool_t)
    COLOR_SEN,      // measure_color_vals (int16_t)
    GYRO_SEN,       // measure_gyro_val (int16_t)
    SONIC_SEN,      // measure_sonic_val (int16_t)
    ENCODER_LR,      // measure_encoderL_val (int32_t)
    ENCODER_ARM    // measure_encoderARM_val (int32_t)
}LogTgt;

/* private functions */
void printTimeStamp(FILE* fp);

/* external variables*/

/* external functions*/
extern void printBtnLog(enum LogTgt SenType, bool TgtState);
extern void printSenLog(enum LogTgt SenType, int TgtVal);
extern void printEncLog(enum LogTgt SenType, int32_t EncVal);

#endif /* _LOG_H */
