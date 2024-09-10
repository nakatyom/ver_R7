#ifndef _GYAK_MIN_H
#define _GYAK_MIN_H


#include "coordinate.h"

/* external functions*/
extern void calc_tgtV(struct coordinate* tgt_coordinate, struct coordinate* crnt_coordinate);
extern void get_tgtVW(float* Tgt_v, float Tgt_w);
extern void reset_tgtV();

#endif /* _GYAK_MIN_H */