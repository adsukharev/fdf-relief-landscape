

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
    double      gradus_axis;

}               t_map;

/* ***************************map.c****************************************** */
t_map *init_map(void);
int fill_map(char *arg, t_map *map, t_vector *v);

/* ***************************vector.c****************************************** */
t_vector     init_vector(int num);
void    push_back(t_vector *v, t_point el);
void free_points(t_vector *v);

/* ***************************modify.c****************************************** */
void rotate(t_point *point,  double rotation);
void iso(t_point *point);
void scale(t_point old, t_point *new, int zoom);
void movements(t_point *point, int offset_x, int offset_y);

/* ***************************alg_bbashiri.c****************************************** */
void algorithm(int x1, int y1, int x2, int y2, t_map *map);
int draw(t_map *map, t_point *point);
int manage_bbashiri(t_map *map);

/* ***************************keyboard_events.c****************************************** */
int key_release(int keycode, t_map *map);


#endif
