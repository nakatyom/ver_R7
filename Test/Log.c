#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "Log.h"


/* private valiables */
bool is_head_btn = true;
bool is_head_sen = true;
bool is_head_enc = true;

/* private functions */

void printTimeStamp(FILE* fp){  // Assuming that the file is opened correctly.
    /* get current time */
    time_t now = time(NULL);
    struct tm* gm_time = gmtime(&now);

    /* add Time Stamp */
    fprintf(fp, "Logging Date is...\n");
    fprintf(fp, "%d/%d/%d_",gm_time->tm_year,gm_time->tm_mon,gm_time->tm_mday);
    fprintf(fp, "%d:%d:%d\n\n",gm_time->tm_hour,gm_time->tm_min,gm_time->tm_sec);

}

/* external functions */


