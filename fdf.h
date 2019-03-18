

#ifndef FDF_CLION_FDF_H
# define FDF_CLION_FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include "math.h"

# define WINDOW_WIDTH   1000
# define WINDOW_HEIGHT	600

typedef struct  s_point
{
    int         x;
    int         y;
    int         z;
    int         colour;
}               t_point;

typedef struct  s_vector
{
    t_point     *point;
    int         size;
    int         cap;
}               t_vector;

typedef struct  s_map
{
    t_vector    *vector;
    int         width;
    int         height;
    void        *mlx_ptr;
    void        *win_ptr;
    int         offset_x;
    int         offset_y;
    int         zoom;
    char        axis;
    int         gradus_axis;

}               t_map;

t_map *init_map(void);
void fill_map(char *arg, t_map *map, t_vector *v);

t_vector     init_vector(int num);
void    push_back(t_vector *v, t_point el);
void free_points(t_vector *v);

void algorithm(int x1, int y1, int x2, int y2, t_map *map);
void manage_bbashiri(t_map *map);

#endif
