#ifndef _GYAK_MIN_H
#define _GYAK_MIN_H

/* external functions*/
extern void get_TgtVelocity(float tgt_dist, float tgt_time, int div_num, float* div_time, float* tgt_velocity);
extern void get_TgtRate(float tgt_theta, float tgt_time, int div_num, float* div_time, float* tgt_rate);

#endif /* _GYAK_MIN_H */