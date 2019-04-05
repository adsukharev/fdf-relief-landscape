
#include "fdf.h"


//int av, char **arg
int main(int av, char **arg) {
    t_vector ve;
    t_map *map;

    map = init_map();
    ve = init_vector(10);
    map->vector = &ve;
    if (!(fill_map(arg[1], map, map->vector)))
    {
        printf("invalid map");
        return (0);
    }
//  if (!(fill_map("/Users/andrei/hack/school42/fdf_cLion/42.fdf", map, map->vector)))
//  {
//      printf("invalid map");
//      return (0);
//  }
    map->mlx_ptr = mlx_init();
    map->win_ptr = mlx_new_window(map->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "bbashiri/ngunthor");
    manage_bbashiri(map);
    mlx_hook(map->win_ptr, 3, 1, key_release, map);
//    mlx_loop_hook(map->mlx_ptr, manage_bbashiri, map);
    mlx_loop(map->mlx_ptr);
    free_points(map->vector);
    return (1);
}

//    int i = 0;
//    while (i < map->vector->size)
//    {
//        if (map->vector->point[i].x == -9)
//            printf("\n");
//        printf("%3d", map->vector->point[i].z);
//        i++;
//    }

//    while (i < v.size)
//    {
//        if (v.point[i].x == 0)
//            printf("\n");
//        printf("%3d", v.point[i].z);
//        i++;
//    }
//    printf("height: %d\n width: %d", map->height, map->width);

