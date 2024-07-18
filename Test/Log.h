#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* private functions */
void printTimeStamp(struct FILE* fp, int mode);

/* external functions*/
extern void printBatLog(int TgtVlt, int TgtCur);
extern void printBtnLog(char* TgtName, bool TgtState);
extern void printColorLog(uint8_t TgtColorVal);
extern void printGyroLog(int16_t TgtGyroVal);
extern void printSonicLog(int16_t TgtSonicVal);
extern void printEncLRLog(int32_t EncLVal, int32_t EncRVal);
extern void printEncArmLog(int32_t EncArmVal);

#endif /* _LOG_H */