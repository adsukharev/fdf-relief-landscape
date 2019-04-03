#include "fdf.h"

int key_release(int keycode, t_map *map)
{

    mlx_clear_window(map->mlx_ptr, map->win_ptr);
    map->offset_x = 0;
    map->offset_y = 0;

    if (keycode == 123)
    {
        map->offset_x = -20;
    }
    else if (keycode == 126)
    {
        map->offset_y = -20;
    }
    else if (keycode == 124)
    {
        map->offset_x = 20;
    }
    else if (keycode == 125)
    {
        map->offset_y = 20;
    }
    if (keycode == 12)
    {
        int i = 0;
        while (i < map->vector->size)
        {
            rotate(&map->vector->point[i].x, &map->vector->point[i].y, &map->vector->point[i].z, map->gradus_axis);
            i++;
        }
    }
    draw(map, map->vector->point);
    return (1);
}
