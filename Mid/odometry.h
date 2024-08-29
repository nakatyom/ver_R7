#ifndef _ODOMETRY_H
#define _ODOMETRY_H

extern struct coordinate{
    int x;
    int y;
    int theta;
};

extern struct coordinate crnt_coordinate;
extern struct coordinate  pre_coordinate;

/* static function */


/* external functions*/
extern coordinate get_crntCoordinate(void);

#endif /* _ODOMETRY_H */