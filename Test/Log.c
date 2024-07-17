#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Log.h"


/* private valiables */
is_head_btn = true;
is_head_sen = true;
is_head_enc = true;

/* private functions */

/* Assuming that the file is opened correctly. */
void printTimeStamp(FILE* fp){
    /* get current time */
    now = time(NULL);
    gm_time = gmtime(&now);

    /* add Time Stamp */
    fprintf(&fp, "Logging Date is...\n");
    fprintf(&fp, "%d/%d/%d_",gm_time->tm_year,gm_time->tm_mon,gm_time->tm_mday);
    fprintf(&fp, "%d:%d:%d\n\n",gm_time->tm_hour,gm_time->tm_min,gm_time->tm_sec);

}

/* external functions */


