
#include "fdf.h"

void		perspective(t_point *p)
{
    float x;
    float y;
    float z;

    x = p->x;
    y = p->y;
    z = p->z;
    p->x = x / (-0.005f * z + 1.0f);
    p->y = y / (-0.005f * z + 1.0f);
    p->z = z / (-0.005f * z + 1.0f);
}

void iso(t_point *point)
{
    int previous_x;
    int previous_y;

    previous_x = point->x;
    previous_y = point->y;
    point->x = (previous_x - previous_y) * cos(0.523599);
    point->y = -point->z + (previous_x + previous_y) * sin(0.523599);
}

void		dimetric(t_point *p)
{
    float x;
    float y;

    x = p->x;
    y = p->y;
    p->x = x * cos(0.122173f) + (y * cos(0.733038f) * 0.5f);
    p->y = -p->z + (y * sin(0.733038f) * 0.5f) - x * sin(0.122173f);
}