
#include "fdf.h"


//int av, char **arg

static t_map *init_map(void)
{
    t_map *map;

    if (!(map = (t_map *)malloc(sizeof(t_map))))
        return (NULL);
    map->width = 0;
    map->height = 0;
    map->zoom = 5;
    map->offset_x = WINDOW_WIDTH / 2;
    map->offset_y = WINDOW_HEIGHT / 2;
    map->gradus_axis = 0;
    map->camera = 1;
    return (map);
}

int main(void)
{
    t_vector ve;
    t_map *map;

    map = init_map();
    ve = init_vector(10);
    map->vector = &ve;
    if (!(fill_map("/Users/andrei/hack/school42/fdf_final/maps/diana.fdf", map)))
    {
        printf("invalid map");
        return (0);
    }
//  if (!(fill_map("/Users/bbashiri/andrey/fdf_new/maps/elem-col.fdf", map, map->vector)))
//  {
//      printf("invalid map");
//      return (0);
//  }

//    printf("%d\n", map->width);
//    printf("%d\n", map->height);
//    int i = 0;
//    while (i < map->vector->size)
//    {
//        printf("x: %d y:%d z:%d c: %d\n", map->vector->point[i].x, map->vector->point[i].y, map->vector->point[i].z, map->vector->point[i].colour);
//        i++;
//    }

//    int i = 0;
//    while (i < map->vector->size)
//    {
////        if (i == map->width)
//        if (map->vector->point[i].colour != 16777215)
//            printf("%d, %d ",map->vector->point[i].z, map->vector->point[i].colour);
//        i++;
//    }
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
