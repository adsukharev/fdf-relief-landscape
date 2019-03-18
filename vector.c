#include "fdf.h"

t_vector     init_vector(int num)
{
    t_vector el;

    el.point = (t_point*)malloc(sizeof(t_point) * num);
    el.cap = num;
    el.size = 0;
    return (el);
}

static void	copy_points(t_point *new, t_point *old, int i)
{
    while (i >= 0)
    {
        new[i] = old[i];
        i--;
    }
}

static void    resize(t_vector *v)
{
    t_point *n_points;

    v->cap = v->cap*2;
    n_points = (t_point*)malloc(sizeof(t_point) * v->cap);
    copy_points(n_points, v->point, v->size);
    free(v->point);
    v->point = n_points;

}

void    push_back(t_vector *v, t_point el)
{
    int i;

    i = v->size;
    if (i == v->cap)
        resize(v);
    v->point[i].x = el.x;
    v->point[i].y = el.y;
    v->point[i].z = el.z;
    //TODO color
    v->size++;
}

void free_points(t_vector *v)
{
    int i;

    i = 0;
    while (i < v->size)
    {
        free(&v->point[i++]);
    }
}