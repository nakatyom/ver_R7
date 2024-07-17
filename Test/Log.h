#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdlib.h>


/* enum */
extern enum LogTgt {
    BATTERY,        // measure_battery_val (int)
    BUTTON,         // measure_button_state (bool_t)
    COLOR_SEN,      // measure_color_vals (int16_t)
    GYRO_SEN,       // measure_gyro_val (int16_t)
    SONIC_SEN,      // measure_sonic_val (int16_t)
    ENCODER_L,      // measure_encoderL_val (int32_t)
    ENCODER_R,      // measure_encoderR_val (int32_t)
    ENCODER_ARM,    // measure_encoderARM_val (int32_t)
};

/* struct */

/* private variables */
bool is_head_btn;
bool is_head_sen;
bool is_head_enc;

/* private functions */
void printTimeStamp();

/* external variables*/

/* external functions*/
extern void printBtnLog(LogTgt SenType, bool_t TgtState);
extern void printSenLog(LogTgt SenType, int TgtVal);
extern void printEncLog(LogTgt SenType, int32_t EncVal);

#endif /* _LOG_H */