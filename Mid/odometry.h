#ifndef _ODOMETRY_H
#define _ODOMETRY_H

extern struct coordinate;

/* external functions*/
extern void get_crntCoordinate(struct coordinate* crnt_coordinate);
extern void get_preCoordinate(struct coordinate* pre_coordinate);

#endif /* _ODOMETRY_H */