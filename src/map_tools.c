
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

int ft_atohex(const char *str)
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

int	ft_doublestrlen(char **s)
{
    int	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
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