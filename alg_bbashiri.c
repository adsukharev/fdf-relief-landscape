#include "fdf.h"

void algorithm(int x1, int y1, int x2, int y2, int colour, t_map *map)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;
    mlx_pixel_put(map->mlx_ptr, map->win_ptr, x2, y2, colour);
    while(x1 != x2 || y1 != y2)
    {
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x1, y1, colour);
        const int error2 = error * 2;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

int draw(t_map *map, t_point *point)
{
    int i;

    i = 0;
    while (i + 1 < map->vector->size)
    {
        if ((i + 1) % (map->width))
        {
            algorithm(point[i].x, point[i].y, point[i + 1].x, point[i + 1].y, point[i + 1].colour, map);
        }
        if (i < ((map->height - 1) * map->width))
        {
            algorithm(point[i].x, point[i].y, point[i + map->width].x, point[i + map->width].y,  point[i + 1].colour, map);
        }
        i++;
    }
    return (1);
}

void draw_text(t_map *map)
{
    mlx_string_put(map->mlx_ptr, map->win_ptr, 0, 0, 16777215, " 'c' - change perspective");
    mlx_string_put(map->mlx_ptr, map->win_ptr, 0, 20, 16777215, " 'q' - rotate");
    mlx_string_put(map->mlx_ptr, map->win_ptr, 0, 40, 16777215, " scroll mouse - zoom");
    mlx_string_put(map->mlx_ptr, map->win_ptr, 0, 60, 16777215, " left right up down - move");
}

int manage_bbashiri(t_map *map) {

    int i;
    t_vector vector;

    vector = init_vector(map->vector->size);
    draw_text(map);
    i = 0;
    while (i < map->vector->size)
    {
        scale(map->vector->point[i], &vector.point[i], map->zoom);
        if (map->gradus_axis != 0)
            rotate(&vector.point[i], map->gradus_axis);
        if (map->camera == 1)
            iso(&vector.point[i]);
        else if (map->camera == 2)
            perspective(&vector.point[i]);
        else
            dimetric(&vector.point[i]);
        movements(&vector.point[i], map->offset_x, map->offset_y);
        i++;
    }
    draw(map, vector.point);
    free_points(&vector);
    return (1);
}
