
#include "fdf.h"

int	deal_key(int key, void *param)
{
	ft_putchar('X');
	return (0);
}

int     ft_count_digit(char *str)
{
    int i;
    int len;

    i = 0;
    len = (int)ft_strlen(str);
    while (len--)
    {
        if (ft_isdigit(str[i]))
            i++;
    }
    return (i);
}

void fill_map(char *arg, t_map *map)
{
    int fd;
    char *str;
    int sign;
    int len;
    int i;

    i = 0;
    sign = 1;
    fd = open(arg, O_RDONLY);
    while (sign)
    {
        sign = get_next_line(fd, &str);
        i += sign == 1 ? 1 : 0;
    }
    close(fd);
    map->xyz = (int ***)malloc(sizeof(int **) * i);
    fd = open(arg, O_RDONLY);
    sign = 1;
    i = 0;
    while (sign)
    {
        sign = get_next_line(fd, &str);
        i = 0;
        while (i < len)
        {
            if (ft_isdigit(str[i]))
            {
                map->width++;
            }
            i++;
        }
    }
    map->xyz[0] = (int **)malloc(sizeof(int *) * i);


}

int main(int av, char **arg)
{
    void *mlx_ptr;
    void *win_ptr;
    int i;
    t_map   *map;

    i = 150;
    if (av < 2)
        return (0);
    fill_map(arg[1], map);

//    mlx_ptr = mlx_init ();
////    win_ptr = mlx_new_window(mlx_ptr, 500, 500, "42");
//    while (i < 300)
//    {
//        mlx_pixel_put(mlx_ptr, win_ptr, i, i, 0x8396ff);
//        i++;
//    }

//	mlx_key_hook(win_ptr, deal_key, (void *)0);
//    mlx_string_put(mlx_ptr, win_ptr, 300, 300, 0x8396ff, "asdasdasdas");
//    mlx_loop(mlx_ptr);

    return 0;
}
