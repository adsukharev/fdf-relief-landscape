
#include "fdf.h"

static int convert_to_nbm(char c)
{
    if (c >= 'a' && c <= 'z')
        c = c - 'a' + 10;
    else if (c >= 'A' && c <= 'Z')
        c = c - 'A' + 10;
    else if (c >= '0' && c <= '9')
        c = c - '0';
    else
        return (-1);
    return (c);
}

static  int ft_atohex(const char *str)
{
    int			i;
    int		res;
    int     converted;

    i = 0;
    res = 0;
    while (str[i])
    {
        converted = convert_to_nbm(str[i++]);
        if (converted == -1)
            return (-1);
        res = converted + res * 16;
    }
    return (res);
}

int parse_z_colour(char *split, t_map *map, int x)
{
    t_point point;
    int i;

    i = 0;
    while (split[i] && split[i] != ',')
    {
        if (!(ft_isdigit(split[i])) && split[i] != '-')
            return (0);
        i++;
    }
    point.colour = 10777215;
    if (split[i] == ',')
    {
        if (split[i + 1] == '0' && (split[i + 2] == 'x' || split[i + 2] == 'X'))
        {
            point.colour = ft_atohex(&split[i + 3]);
            if (point.colour == -1)
                return (0);
        }
        else
            return (0);
    }
    point.y = map->height;
    point.x = x - map->width / 2;
    point.z = ft_atoi(split);
    push_back(map->vector, point);
    return (1);
}

int cycle_parse(char **split, t_map *map)
{
    int i;

    i = 0;
    while (split[i])
    {
        if (parse_z_colour(split[i], map, i) == 0)
            return (0);
        i++;
    }
    return (1);
}

int	ft_doublestrlen(char **s)
{
    int	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}


int get_first_line(int fd, t_map *map)
{
    char *gnl;
    char **split;

    get_next_line(fd, &gnl);
    if (!gnl)
        return (0);
    split = ft_strsplit(gnl, ' ');
    ft_strdel(&gnl);
    map->width = ft_doublestrlen(split);
    map->height = 1;
    if (cycle_parse(split, map) == 0)
        return (0);
    ft_strdelite(split, map->width);
    return (1);
}

void change_height(t_map *map)
{
    int i;

    i = 0;
    while (i < map->vector->size)
    {
        map->vector->point[i].y -= map->height / 2;
        i++;
    }
}

int fill_map(char *arg, t_map *map)
{
    int fd;
    char *gnl;
    char **split;
    int validate_width;

    fd = open(arg, O_RDONLY);
    if (get_first_line(fd, map) == 0)
        return (0);
    while (get_next_line(fd, &gnl))
    {
        split = ft_strsplit(gnl, ' ');
        ft_strdel(&gnl);
        map->height++;
        validate_width = ft_doublestrlen(split);
        if (validate_width != map->width)
            return (0);
        if (cycle_parse(split, map) == 0)
            return (0);
        ft_strdelite(split, map->width);
    }
    change_height(map);
    close(fd);
    return (1);
}
