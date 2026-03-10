#ifndef ACTION_H__
#define ACTION_H__

typedef struct move_t
{
    double dx;
    double dy;
    double dz;
} move_t;

typedef struct scale_t
{
    double kx;
    double ky;
    double kz;
} scale_t;

typedef struct rotate_t
{
    double angle_x;
    double angle_y;
    double angle_z;
} rotate_t;

#endif
