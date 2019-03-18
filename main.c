
#include "fdf.h"

int	deal_key(int key, void *param)
{
	ft_putchar('X');
	return (0);
}


int main(int av, char **arg)
{
    t_vector ve;
    t_map   *map;

    //TODO args
    map = init_map();
    ve = init_vector(10);
    map->vector = &ve;
    fill_map(arg[1], map, map->vector);
    map->mlx_ptr = mlx_init();
    map->win_ptr = mlx_new_window(map->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "bbashiri/ngunthor");

    mlx_hook(map->win_ptr, int x_event, int x_mask, int (*funct)(), (void *)0);
    manage_bbashiri(map);
    mlx_loop(map->mlx_ptr);
    free_points(map->vector);
    return 0;


//  fill_map("/Users/bbashiri/andrey/fdf_cLion/42.fdf", map, map->vector);



//    mlx_key_hook(win_ptr, deal_key, (void *)0);
//    mlx_string_put(mlx_ptr, win_ptr, 300, 300, 0x8396ff, "asdasdasdas");






//    while (i < v.size)
//    {
//        if (v.point[i].x == 0)
//            printf("\n");
//        printf("%3d", v.point[i].z);
//        i++;
//    }
//    printf("height: %d\n width: %d", map->height, map->width);


}
