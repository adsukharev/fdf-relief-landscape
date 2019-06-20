
#ifndef FDF_CLION_FDF_H
# define  FDF_CLION_FDF_H

# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include "math.h"

# define  WINDOW_WIDTH  1000
# define  WINDOW_HEIGHT 600

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
    char        camera;
    int         colour;
}               t_map;
/* ***************************map.c****************************************** */
int             fill_map(char *arg, t_map *map);
/* ***************************map.c****************************************** */
int             ft_atohex(const char *str);
int             ft_doublestrlen(char **s);
void            change_height(t_map *map);
/* ***************************vector.c****************************************** */
t_vector        init_vector(int num);
void            push_back(t_vector *v, t_point el);
void            free_points(t_vector *v);
/* ***************************modify.c****************************************** */
void            rotate(t_point *point,  double rotation);
void            scale(t_point old, t_point *new, int zoom);
void            movements(t_point *point, int offset_x, int offset_y);
/* ***************************camera.c****************************************** */
void            iso(t_point *point);
void            perspective(t_point *p);
void            dimetric(t_point *p);
/* ***************************draw.c****************************************** */
int             manage_bbashiri(t_map *map);
/* ***************************keyboard_events.c****************************************** */
int             key_release(int keycode, t_map *map);
int             mouse_press(int button, int x, int y, t_map *map);
#endif
