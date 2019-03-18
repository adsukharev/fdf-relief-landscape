#include "fdf.h"

void algorithm(int x1, int y1, int x2, int y2, t_map *map)
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    mlx_pixel_put(map->mlx_ptr, map->win_ptr, x2, y2, 0x8396ff);
    while(x1 != x2 || y1 != y2)
    {
        mlx_pixel_put(map->mlx_ptr, map->win_ptr, x1, y1, 0x8396ff);
        const int error2 = error * 2;
        //
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

//    const int deltaX = abs(map->vector->point[i + 1].x - map->vector->point[i].x);
//    const int deltaY = abs(map->vector->point[i + 1].y - map->vector->point[i].y);
//    const int signX = map->vector->point[i].x < map->vector->point[i + 1].x ? 1 : -1;
//    const int signY = map->vector->point[i].y < map->vector->point[i + 1].y ? 1 : -1;
//    int error = deltaX - deltaY;
//
//    mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->vector->point[i + 1].x, map->vector->point[i + 1].y, 0x8396ff);
//    while(map->vector->point[i].x != map->vector->point[i + 1].x || map->vector->point[i].y != map->vector->point[i + 1].y)
//    {
//        mlx_pixel_put(map->mlx_ptr, map->win_ptr, map->vector->point[i].x, map->vector->point[i].y, 0x8396ff);
//        const int error2 = error * 2;
//        if(error2 > -deltaY)
//        {
//            error -= deltaY;
//            map->vector->point[i].x += signX;
//        }
//        if(error2 < deltaX)
//        {
//            error += deltaX;
//            map->vector->point[i].y += signY;
//        }
//    }
//}

static void rotate(int *x, int *y, int *z, char c, double rotation)
{
    int previous_x;
    int previous_y;
    int previous_z;

    previous_x = *x;
    previous_y = *y;
    previous_z = *z;
    if (c == 'x')
    {
        *y = previous_y * cos(rotation) + previous_z * sin(rotation);
        *z = -previous_y * sin(rotation) + previous_z * cos(rotation);
    }
    else if (c == 'y')
    {
        *x = previous_x * cos(rotation) + previous_z * sin(rotation);
        *z = -previous_x * sin(rotation) + previous_z * cos(rotation);
    }
    else if (c == 'z')
    {
        *x = previous_x * cos(rotation) - previous_y * sin(rotation);
        *y = previous_x * sin(rotation) + previous_y * cos(rotation);
    }
    else
        return;
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}


static  void scale(t_map *map, int i)
{
    map->vector->point[i].x *= map->zoom ;
    map->vector->point[i].y *= map->zoom ;
    map->vector->point[i].z *= map->zoom / 5 ;

}

static  void movements(t_map *map, int i)
{
    map->vector->point[i].x += map->offset_x;
    map->vector->point[i].y += map->offset_y;
//    map->vector->point[i].z += map->offset;
}

void manage_bbashiri(t_map *map) {

    int i;

    i = 0;


//    scale(map);
//    rotate(&map->vector->point[i].x, &map->vector->point[i].y, &map->vector->point[i].z, 'y', 0.5);
//    iso(&map->vector->point[i].x, &map->vector->point[i].y , map->vector->point[i].z);
//    centrelization(map);
    while (i < map->vector->size)
    {
        scale(map, i);
        rotate(&map->vector->point[i].x, &map->vector->point[i].y, &map->vector->point[i].z, map->axis, map->gradus_axis);
        iso(&map->vector->point[i].x, &map->vector->point[i].y , map->vector->point[i].z);
        movements(map, i);
        i++;
    }
    i = 0;
    while (i + 1 < map->vector->size)
    {
        if ((i + 1) % (map->width))
        {
            algorithm(map->vector->point[i].x, map->vector->point[i].y, map->vector->point[i + 1].x,
                      map->vector->point[i + 1].y, map);
        }
        if (i < ((map->height - 1) * map->width))
        {
            algorithm(map->vector->point[i].x, map->vector->point[i].y, map->vector->point[i + map->width].x,
                      map->vector->point[i + map->width].y, map);
        }
        i++;
    }
}


