#include "fdf.h"

int key_release(int keycode, t_map *map)
{
    mlx_clear_window(map->mlx_ptr, map->win_ptr);
    if (keycode == 12)
    {
        map->offset_x += 50;
    }

    manage_bbashiri2(map);
    return (1);
}
