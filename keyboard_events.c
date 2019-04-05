#include "fdf.h"

int key_release(int keycode, t_map *map)
{
    mlx_clear_window(map->mlx_ptr, map->win_ptr);
    if (keycode == 53)
    {
        exit(0);
    }
    if (keycode == 123)
    {
        map->offset_x -= 20;
    }
    else if (keycode == 126)
    {
        map->offset_y -= 20;
    }
    else if (keycode == 124)
    {
        map->offset_x += 20;
    }
    else if (keycode == 125)
    {
        map->offset_y += 20;
    }
    if (keycode == 12)
    {
        map->gradus_axis += 0.1;
        if (map->gradus_axis == 1.0)
            map->gradus_axis = 0;
    }
    manage_bbashiri(map);
    return (1);
}
