#ifndef _GYAK_MIN_H
#define _GYAK_MIN_H

/* external functions*/
extern void calc_TgtVelocity(float tgt_dist, float tgt_time, int div_num, float* div_time, float* tgt_velocity);
extern void calc_TgtRate(float tgt_theta, float tgt_time, int div_num, float* div_time, float* tgt_rate);
extern float get_TgtVelocity(float crnt_dist, int div_num, float* div_time, float* tgt_velocity);
extern float get_TgtRate(float crnt_theta, int div_num, float* div_time, float* tgt_rate);

/* using odometry */
extern void gyak_velocity_control(float, float);

#endif /* _GYAK_MIN_H */