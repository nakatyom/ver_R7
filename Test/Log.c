#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Log.h"


/* define */
#define FILE_PATH_BAT  ""
#define FILE_PATH_BTN ""
#define FILE_PATH_COLOR ""
#define FILE_PATH_GYRO ""
#define FILE_PATH_SONIC ""
#define FILE_PATH_ENC_LR ""
#define FILE_PATH_ENC_ARM "" 

/* private valiables */
bool is_head_bat = true;
bool is_head_btn = true;
bool is_head_color = true;
bool is_head_gyro = true;
bool is_head_sonic = true;
bool is_head_encLR = true;
bool is_head_encArm = true;

/* private functions */

void printTimeStamp(struct FILE* fp, bool is_head){  // Assuming that the file is opened correctly.
    /* get current time */
    time_t now = time(NULL);
    struct tm* gm_time = gmtime(&now);

    /* add Date Stamp */
    if(is_head == true){
        fprintf(fp, "Logging Date is...\n");
        fprintf(fp, "%d/%d/%d\n",gm_time->tm_year,gm_time->tm_mon,gm_time->tm_mday);
        is_head = false;
    }

    /* add Time Stamp */
    else if(is_head == false) fprintf(fp, "%d:%d:%d | ",gm_time->tm_hour,gm_time->tm_min,gm_time->tm_sec);
}

/* external functions */
extern void printBatLog(int TgtVlt, int TgtCur){
    // open Target file.
    struct FILE* fp = fopen(FILE_PATH_BAT, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Vlotage Val | Current Val
    printTimeStamp(fp, is_head_bat);
    fprintf(fp, "%d | ", TgtVlt);
    fprintf(fp, "%d\n", TgtCur);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printBtnLog(char* TgtName, bool TgtState){
    // open Target file.
    struct FILE* fp = fopen(FILE_PATH_BTN, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Button Name | State
    printTimeStamp(fp, is_head_btn);
    fprintf(fp, "%s | ", TgtName);
    fprintf(fp, "%d\n", TgtState);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printColorLog(uint8_t TgtColorVal){
    // open Target file.
    struct FILE* fp = fopen(FILE_PATH_COLOR, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Color Val
    printTimeStamp(fp, is_head_color);
    fprintf(fp, "%d\n", TgtColorVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printGyroLog(uint16_t TgtGyroVal){
    // open Target file.
    struct FILE* fp = fopen(FILE_PATH_GYRO, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Gyro Val
    printTimeStamp(fp, is_head_gyro);
    fprintf(fp, "%d\n", TgtGyroVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printSonicLog(uint16_t TgtSonicVal){
    // open Target file.
    struct FILE* fp = fopen(FILE_PATH_SONIC, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Sonic Val
    printTimeStamp(fp, is_head_sonic);
    fprintf(fp, "%d\n", TgtSonicVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printEncLRLog(int32_t EncLVal, int32_t EncRVal){
    // open Target file.
    struct FILE* fp = fopen(FILE_PATH_ENC_LR, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Encoder_L val | Encoder_R val
    printTimeStamp(fp, is_head_encLR);
    fprintf(fp, "%d | ", EncLVal);
    fprintf(fp, "%d\n", EncRVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printEncArmLog(int32_t EncArmVal){
    // open Target file.
    struct FILE* fp = fopen(FILE_PATH_ENC_ARM, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Encoder_Arm Val
    printTimeStamp(fp, is_head_encArm);
    fprintf(fp, "%d\n", EncArmVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}
