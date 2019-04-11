
#include "fdf.h"

void rotate(t_point *point,  double rotation)
{
    float p_x;
    float p_y;
    float p_z;

    p_x = point->x;
    p_y = point->y;
    p_z = point->z;

    point->x = p_x;
    point->y = p_y * cos(rotation) + p_z * sin(rotation);
    point->z = -p_y * sin(rotation) + p_z * cos(rotation);

    p_x = point->x;
    p_y = point->y;
    p_z = point->z;

    point->x = p_x * cos(rotation) + p_z * sin(rotation);
    point->y = p_y;
    point->z = -p_x * sin(rotation) + p_z * cos(rotation);

    p_x = point->x;
    p_y = point->y;
    p_z = point->z;

    point->x = p_x * cos(rotation) - p_y * sin(rotation);
    point->y = p_x * sin(rotation) + p_y * cos(rotation);
    point->z = p_z;

}

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

void scale(t_point old, t_point *new, int zoom)
{
    new->x = old.x * zoom;
    new->y = old.y * zoom;
    new->z = old.z * sqrt(zoom);
    new->colour = old.colour;
}

void movements(t_point *point, int offset_x, int offset_y)
{
    point->x += offset_x;
    point->y += offset_y;
}
