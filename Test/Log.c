#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Log.h"

/* define */
#define FILE_PATH_BAT  "log_bat.txt"
#define FILE_PATH_BTN "log_btn.txt"
#define FILE_PATH_COLOR "log_color.txt"
#define FILE_PATH_GYRO "log_gyro.txt"
#define FILE_PATH_SONIC "log_sonic.txt"
#define FILE_PATH_ENC_LR "log_encLR.txt"
#define FILE_PATH_ENC_ARM "log_encArm.txt" 

/* private valiables */
static bool is_head_bat = true;
static bool is_head_btn = true;
static bool is_head_color = true;
static bool is_head_gyro = true;
static bool is_head_sonic = true;
static bool is_head_encLR = true;
static bool is_head_encArm = true;


/* private functions */
void printTimeStamp(FILE *fp, bool is_head){  // Assuming that the file is opened correctly.
    
    struct timeval tvToday;
    struct tm *gm_time;

    /* get current time */
    gettimeofday(&tvToday, NULL); // Today
    gm_time = localtime(&tvToday.tv_sec);

    /* add Date Stamp (1 time)*/
    if(is_head == true){
        fprintf(fp, "Logging Date is...\n");
        fprintf(fp, "%d/%d/%d\n",gm_time->tm_year+1900,gm_time->tm_mon+1,gm_time->tm_mday);
        is_head = false;
    }

    /* add Time Stamp */
    fprintf(fp, "Logging time is...\n");
    fprintf(fp, "%d:%d:%d | ",gm_time->tm_hour,gm_time->tm_min,gm_time->tm_sec);
}


/* external functions */
void printBatLog(int TgtVlt, int TgtCur){
    // open Target file.
    FILE *fp = fopen(FILE_PATH_BAT, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Vlotage Val | Current Val
    printTimeStamp(fp, is_head_bat);
    fprintf(fp, "Battery_volt = %d[mV], ", TgtVlt);
    fprintf(fp, "Battery_current = %d[mA]\n", TgtCur);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}


void printBtnLog(char* TgtName, bool TgtState){
    // open Target file.
    FILE* fp = fopen(FILE_PATH_BTN, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Button Name | State
    printTimeStamp(fp, is_head_btn);
    fprintf(fp, "%s = ", TgtName);
    fprintf(fp, "%d\n", TgtState);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

void printColorLog(u_int8_t Ambient, u_int8_t Reflect, rgb_raw_t* TgtColorVal){
    // open Target file.
    FILE* fp = fopen(FILE_PATH_COLOR, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }
 
    printf("file open.\n");

    //write Log : Date
    //            Time | Color Val
    printTimeStamp(fp, is_head_color);
    fprintf(fp, "Ambient = %d, ", Ambient);
    fprintf(fp, "Reflect = %d, ", Reflect);
    fprintf(fp, "R:%d, G:%d, B:%d\n", TgtColorVal->r, TgtColorVal->g, TgtColorVal->b);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

void printGyroLog(int16_t TgtGyroVal){
    // open Target file.
    FILE* fp = fopen(FILE_PATH_GYRO, "a");
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

void printSonicLog(int16_t TgtSonicVal){
    // open Target file.
    FILE* fp = fopen(FILE_PATH_SONIC, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Sonic Val
    printTimeStamp(fp, is_head_sonic);
    fprintf(fp, "Distance = %d[cm]\n", TgtSonicVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

void printEncLRLog(int32_t EncLVal, int32_t EncRVal){
    // open Target file.
    FILE* fp = fopen(FILE_PATH_ENC_LR, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Encoder_L val | Encoder_R val
    printTimeStamp(fp, is_head_encLR);
    fprintf(fp, "%ld | ", EncLVal);
    fprintf(fp, "%ld\n", EncRVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

void printEncArmLog(int32_t EncArmVal){
    // open Target file.
    FILE* fp = fopen(FILE_PATH_ENC_ARM, "a");
    if(fp == NULL){
        printf("fail open file on Log.c");
        return;
    }

    //write Log : Date
    //            Time | Encoder_Arm Val
    printTimeStamp(fp, is_head_encArm);
    fprintf(fp, "%ld\n", EncArmVal);

    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}
