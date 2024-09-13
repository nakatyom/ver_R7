#ifndef _COMMON_H
#define _COMMON_H

#define PI_FLOAT    3.141592f   // 円周率

extern struct coordinate{
    float x;
    float y;
    float theta;
};

extern float trans_gDeg(float encdeg);
extern void transPolor(struct coordinate* crnt, struct coordinate* trgt, float* dist, float* theta);

#endif /* _COMMON_H */

