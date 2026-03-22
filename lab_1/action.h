#ifndef ACTION_H__
#define ACTION_H__

typedef struct move_data_t
{
    double dx;
    double dy;
    double dz;
} move_data_t;

typedef struct scale_data_t
{
    double kx;
    double ky;
    double kz;
} scale_data_t;

typedef struct rotate_data_t
{
    double angle_x;
    double angle_y;
    double angle_z;
} rotate_data_t;

#endif
