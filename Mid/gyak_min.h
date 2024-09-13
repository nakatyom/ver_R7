#ifndef _GYAK_MIN_H
#define _GYAK_MIN_H

/* external functions*/
extern void calc_TgtVelocity(float tgt_dist, float tgt_time, int div_num, float* div_time, float* tgt_velocity);
extern void clac_TgtRate(float tgt_theta, float tgt_time, int div_num, float* div_time, float* tgt_rate);
extern float get_TgtVelcity(float crnt_time, int div_num, float* div_time, float* tgt_velocity);
extern float get_TgtRate(float crnt_time, int div_num, float* div_time, float* tgt_rate);

#endif /* _GYAK_MIN_H */