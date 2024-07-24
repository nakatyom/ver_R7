#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* define */
#define FILE_PATH_BAT  "log_bat.txt"
#define FILE_PATH_BTN "log_btn.txt"
#define FILE_PATH_COLOR "log_color.txt"
#define FILE_PATH_GYRO "log_gyro.txt"
#define FILE_PATH_SONIC "log_sonic.txt"
#define FILE_PATH_ENC_LR "log_encLR.txt"
#define FILE_PATH_ENC_ARM "log_encArm.txt" 

/* private valiables */
static bool is_head_bat;
static bool is_head_btn;
static bool is_head_color;
static bool is_head_gyro;
static bool is_head_sonic;
static bool is_head_encLR;
static bool is_head_encArm;

/* private functions */
static void printTimeStamp(struct FILE* fp, bool is_head);

/* external functions*/
extern void printBatLog(int TgtVlt, int TgtCur);
extern void printBtnLog(char* TgtName, bool TgtState);
extern void printColorLog(u_int8_t TgtColorVal);
extern void printGyroLog(int16_t TgtGyroVal);
extern void printSonicLog(int16_t TgtSonicVal);
extern void printEncLRLog(int32_t EncLVal, int32_t EncRVal);
extern void printEncArmLog(int32_t EncArmVal);

#endif /* _LOG_H */
