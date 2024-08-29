#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Log.h"

/* define */
#define FILE_PATH_MOTOR "log_motor.txt"

/* private valiables */
static bool is_head_motor = true;

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
void log_EncLR(int pwrL, int pwrR, int32_t encL, int32_t encR){
    // open Target file.
    FILE* fp = fopen(FILE_PATH_MOTOR, "a");
    if(fp == NULL){
        printf("failed open file on Log.c\n");
        return;
    }

    //write Log : Date
    //            Time | Encoder_L val | Encoder_R val
    // printTimeStamp(fp, is_head_encLR);
    fprintf(fp, "%ld,", pwrL);
    fprintf(fp, "%ld,", encL);
    fprintf(fp, "%ld,", pwrR);
    fprintf(fp, "%ld\n", encR);

    // close Target file.
    // fprintf(fp,"\n");
    fclose(fp);
}


