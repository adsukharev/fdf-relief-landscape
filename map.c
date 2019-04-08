
#include "fdf.h"

t_map *init_map(void)
{
    t_map *map;

    if (!(map = (t_map *)malloc(sizeof(t_map))))
        return (NULL);
    map->width = 0;
    map->height = 0;
    map->zoom = 10;
    map->offset_x = WINDOW_WIDTH / 2;
    map->offset_y = WINDOW_HEIGHT / 2;
    map->gradus_axis = 0;
    map->colour = 16777215;
    map->camera = 'i';
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

int convert_to_nbm(char c)
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

static  long ft_atohex(const char *str)
{
    int			i;
    long		res;
    int     converted;
    char dict[18];

    ft_strcpy(dict, "0123456789abcdef");
    i = 0;
    while (str[i])
    {
        converted = convert_to_nbm(str[i]);
        res = dict[converted] + res * 10;
    }
    return (res);
}

int count_hex(char *str)
{
    int i;

    i = 0;
    while (str[i] != ' ' && str[i])
    {
        i++;
    }
    return (i);
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
            if (gnl[i] != ' ' && gnl[i] != ',' && !ft_isdigit(gnl[i]))
                return (0);
            if (ft_isdigit(gnl[i]) || gnl[i] == '-' || gnl[i] == '+')
            {
                map->width++;
                i += ft_countint(ft_atoii(&gnl[i])) - 1;
            }
            i++;
            if (gnl[i] == ',')
            {
                if (ft_isdigit(gnl[++i]))
                    i += count_hex(&gnl[i]);
                else
                    return (0);
            }
        }
        ft_strdel(&gnl);
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
            if (gnl[i] == ',')
            {
                if (gnl[++i] != '0')
                    return (0);
                i += 2;
                point.colour = ft_atohex(&gnl[i]);
                i++;
            }
            if (ft_isdigit(gnl[i]) || gnl[i] == '-' || gnl[i] == '+')
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