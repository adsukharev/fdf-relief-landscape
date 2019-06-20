
#include "fdf.h"

static  t_map *init_map(void)
{
    t_map *map;

    if (!(map = (t_map *)malloc(sizeof(t_map))))
    {
      return (NULL);
    }

    map->width = 0;
    map->height = 0;
    map->zoom = 5;
    map->offset_x = WINDOW_WIDTH / 2;
    map->offset_y = WINDOW_HEIGHT / 2;
    map->gradus_axis = 0;
    map->camera = 1;
    return (map);
}

int     main(int ac, char **av)
{
    t_vector  ve;
    t_map     *map;

    if (ac != 2)
    {
      printf("invalid input\n");
      return (0);
    }
    map = init_map();
    ve = init_vector(10);
    map->vector = &ve;
    if (!(fill_map(av[1], map)))
    {
      printf("invalid map\n");
      return (0);
    }
    map->mlx_ptr = mlx_init();
    map->win_ptr = mlx_new_window(map->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "bbashiri/ngunthor");
    manage_bbashiri(map);
    mlx_hook(map->win_ptr, 3, 1, key_release, map);
    mlx_hook(map->win_ptr, 4, 1, mouse_press, map);
//    mlx_loop_hook(map->mlx_ptr, manage_bbashiri, map);
    mlx_loop(map->mlx_ptr);
    free_points(map->vector);
    return (1);
}
