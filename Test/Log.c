#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Log.h"


/* private valiables */
bool is_head_btn = true;
bool is_head_sen = true;
bool is_head_enc = true;

char TgtFilePath_bat[] = "";
char TgtFilePath_btn[] = "";
char TgtFilePath_color[] = "";
char TgtFilePath_gyro[] = "";
char TgtFilePath_sonic[] = "";
char TgtFilePath_encLR[] = "";
char TgtFilePath_encArm[] = ""; 

/* private functions */

void printDateStamp(struct FILE* fp){  // Assuming that the file is opened correctly.
    /* get current time */
    time_t now = time(NULL);
    struct tm* gm_time = gmtime(&now);

    /* add Time Stamp */
    fprintf(fp, "Logging Date is...\n");
    fprintf(fp, "%d/%d/%d\n",gm_time->tm_year,gm_time->tm_mon,gm_time->tm_mday);

}

void printTimeStamp(struct FILE* fp){  // Assuming that the file is opened correctly.
    /* get current time */
    time_t now = time(NULL);
    struct tm* gm_time = gmtime(&now);

    /* add Time Stamp */
    fprintf(fp, "Logging Date is...\n");
    fprintf(fp, "%d/%d/%d_",gm_time->tm_year,gm_time->tm_mon,gm_time->tm_mday);
    fprintf(fp, "%d:%d:%d\n\n",gm_time->tm_hour,gm_time->tm_min,gm_time->tm_sec);

}

/* external functions */
extern void printBatLog(int TgtVlt, int TgtCur){
    // open Target file.
    struct FILE* fp = fopen(TgtFilePath_bat, "a");


    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printBtnLog(char* TgtName, bool TgtState){
    // open Target file.
    struct FILE* fp = fopen(TgtFilePath_btn, "a");


    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printColorLog(uint8_t TgtColorVal){
    // open Target file.
    struct FILE* fp = fopen(TgtFilePath_color, "a");


    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printGyroLog(uint16_t TgtGyroVal){
    // open Target file.
    struct FILE* fp = fopen(TgtFilePath_gyro, "a");


    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printSonicLog(uint16_t TgtSonicVal){
    // open Target file.
    struct FILE* fp = fopen(TgtFilePath_sonic, "a");


    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printEncLRLog(int32_t EncLVal, int32_t EncRVal){
    // open Target file.
    struct FILE* fp = fopen(TgtFilePath_encLR, "a");


    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}

extern void printEncArmLog(int32_t EncArmVal){
    // open Target file.
    struct FILE* fp = fopen(TgtFilePath_encArm, "a");


    // close Target file.
    fprintf(fp,"\n");
    fclose(fp);
}
