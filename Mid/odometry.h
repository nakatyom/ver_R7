#ifndef _ODOMETRY_H
#define _ODOMETRY_H
 
#include "common.h"
 
 
/* external functions*/
extern void get_crntCoordinate(struct coordinate* crnt_coordinate);
extern void get_preCoordinate(struct coordinate* coordinate);
extern void reset_Coordinate();
 
#endif /* _ODOMETRY_H */