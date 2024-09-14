#ifndef _COMMON_H
#define _COMMON_H

#define PI_FLOAT 3.141592f // �?周�?
#define PI_DOUBLE 3.1415926535

extern struct coordinate{
    float x;
    float y;
    float theta;
};

extern float trans_gDeg(float encdeg);
extern float get_dist_p(struct coordinate* crnt, struct coordinate* trgt);
extern int   get_rot_p(struct coordinate* crnt, struct coordinate* trgt);

#endif /* _COMMON_H */

