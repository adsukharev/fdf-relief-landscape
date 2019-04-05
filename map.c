
#include "fdf.h"

t_map *init_map(void)
{
    t_map *map;

    if (!(map = (t_map *)malloc(sizeof(t_map))))
        return (NULL);
    map->width = 0;
    map->height = 0;
    map->zoom = 25;
    map->offset_x = 500;
    map->offset_y = 300;
    map->gradus_axis = 0;

    return (map);
}

static  int	ft_atoii(const char *str)
{
    int				i;
    long long		res;
    int				znak;

    znak = 1;
    res = 0;
    i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
        i++;
    if (str[i] == '-')
    {
        znak = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i++] - '0');
    }
    return (res * znak);
}

static int count_width_height_of_map(t_map *map, char *arg)
{
    int fd;
    int i;
    char *gnl;
    int validate_width;

    fd = open(arg, O_RDONLY);
    while (get_next_line(fd, &gnl))
    {
        map->height++;
        validate_width = map->width;
        if (validate_width != map->width)
            return (0);
        map->width = 0;
        i = 0;
        while (gnl[i])
        {
            if (ft_isdigit(gnl[i]))
            {
                map->width++;
            }
            i++;
        }
    }
    close(fd);
    return (1);
}

int fill_map(char *arg, t_map *map, t_vector *v)
{
    int fd;
    char *gnl;
    int i;
    t_point point;

    if (!(count_width_height_of_map(map, arg)))
        return (0);
    fd = open(arg, O_RDONLY);
    point.y = -map->height / 2;
    while (get_next_line(fd, &gnl))
    {
        point.x = -map->width / 2;
        point.y++;
        i = 0;
        while (gnl[i])
        {
            if (ft_isdigit(gnl[i]))
            {
                point.z = ft_atoii(&gnl[i]);
                i += ft_countint(ft_atoii(&gnl[i])) - 1;
                push_back(v, point);
                point.x++;
            }
            i++;
        }
    }
    close(fd);
    return (1);
}