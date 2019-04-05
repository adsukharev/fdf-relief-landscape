#include "matrix.h"

#include <stdio.h>

#define M_ADDR(matrix) ((matrix_t*)((byte_t*)matrix - sizeof(matrix_t)))

typedef struct matrix
{
    unsigned int rows;
    unsigned int cols;
} matrix_t;

double **create_grid(matrix_t *matrix, unsigned int pointers_size, void *raw, double initial_value)
{
    double **grid = (double**)raw;
    byte_t *raw_bytes = (byte_t*)raw;

    unsigned int i = 0;
    unsigned int j = 0;
    while(i < matrix->rows)
    {
        // EXAMPLE: matrix 3x3
        //                +-------------------------------------------------+
        //          +-----|----------------------------+                    |
        //    +-----|-----|------+                     |                    |
        //    |     |     |   ___|___ ______ ______ ___|__ ______ ______ ___|__ ______ ______
        // | <0> | <1> | <2> |   #   |      |      |   #  |      |      |   #  |      |      |
        // ^-----pointers----^ [0][0] [0][1] [0][2] [1][0] [1][1] [1][2] [2][0] [2][1] [2][2]
        //
        // pointers_size = 3*sizeof(double*)
        //
        grid[i] = (double*)(raw_bytes + pointers_size + i*matrix->cols*sizeof(double));

        j = 0;
        while(j < matrix->cols) 
            grid[i][j++] = initial_value; // Set all to initial_value. (in current row)
        i++;
    }

    return grid;
}

double **matrix(unsigned int rows, unsigned int cols)
{
    return vfmatrix(rows, cols, 0.);
}

double **imatrix(unsigned int size)
{
    return dmatrix(size, 1.);
}

double **dmatrix(unsigned int size, double diagonal_value)
{
    if(!size)
        return NULL;
    
    double **result = matrix(size, size);
    if(!result)
        return NULL;

    unsigned int i = 0;
    while(i < size)
    {
        result[i][i] = diagonal_value;
        i++;
    }

    return result;
}

double **vfmatrix(unsigned int rows, unsigned int cols, double value)
{
    if(rows == 0 || cols == 0)
        return NULL;

    unsigned int pointers_size = rows * sizeof(double*);
    unsigned int matrix_size   = rows * cols * sizeof(double);

    void *raw = malloc(pointers_size + matrix_size + sizeof(matrix_t));
    if(!raw) 
        return NULL;

    matrix_t *matrix = (matrix_t*)raw;
    matrix->rows = rows;
    matrix->cols = cols;
    return create_grid(matrix, pointers_size, (void*)((byte_t*)raw + sizeof(matrix_t)), value);
}

unsigned int mrows(double **m)
{
    if(!m)
        return -1;

    return M_ADDR(m)->rows;
}

unsigned int mcols(double **m)
{
    if(!m)
        return -1;

    return M_ADDR(m)->cols;
}

void mfree(double **matrix)
{
    if(matrix)
        free(M_ADDR(matrix));
}

double **madd(const double **first, const double **second)
{
    if(!first || !second)
        return NULL;

    double **result = mcopy(first);
    if(!result)
        return NULL;

    if(madda(result, second))
    {
        mfree(result);
        return NULL;
    }

    return result;
}

mstatus_t madda(double **dest, const double **second)
{
    if(!dest || !second)
        return ME_NULL;

    matrix_t *m1 = M_ADDR(dest);
    matrix_t *m2 = M_ADDR(second);

    if(m1->rows != m2->rows || m1->cols != m2->cols)
        return ME_ISIZE;

    unsigned int i = 0, j = 0;
    while(i < m1->rows)
    {
        j = 0;
        while(j < m1->cols)
        {
            dest[i][j] += second[i][j];
            j++;
        }
        i++;
    }

    return MSUCCESS;
}

double **mmuld(const double **m, double value)
{
    if(!m)
        return NULL;

    double **result = mcopy(m);
    if(!result)
        return NULL;

    mmulda(result, value);

    return result;
}

mstatus_t mmulda(double **m, double value)
{
    if(!m)
        return ME_NULL;

    matrix_t *matrix = M_ADDR(m);

    unsigned int i = 0, j = 0;
    while(i < matrix->rows)
    {
        j = 0;
        while(j < matrix->cols)
        {
            m[i][j] *= value;
            j++;
        }
        i++;
    }

    return MSUCCESS;
}

double **mmulrd(const double **m, unsigned int row, double value)
{
    if(!m)
        return NULL;

    double **result = mcopy(m);
    if(!result)
        return NULL;

    if(mmulrda(result, row, value))
    {
        mfree(result);
        return NULL;
    }

    return result;
}

mstatus_t mmulrda(double **m, unsigned int row, double value)
{
    if(!m)
        return ME_NULL;

    matrix_t *matrix = M_ADDR(m);
    if(row >= matrix->rows)
        return ME_IINDEX;

    unsigned int j = 0;
    while(j < matrix->cols)
        m[row][j++] *= value;

    return MSUCCESS;
}

double **mmulcd(const double **m, unsigned int col, double value)
{
    if(!m)
        return NULL;

    double **result = mcopy(m);
    if(!result)
        return NULL;

    if(mmulcda(result, col, value))
    {
        mfree(result);
        return NULL;
    }

    return result;
}

mstatus_t mmulcda(double **m, unsigned int col, double value)
{
    if(!m)
        return ME_NULL;

    matrix_t *matrix = M_ADDR(m);

    if(col >= matrix->cols)
        return ME_IINDEX;

    unsigned int i = 0;
    while(i < matrix->rows);
        m[i++][col] *= value;

    return MSUCCESS;
}

double **mswapr(const double **m, unsigned int row_1, unsigned int row_2)
{
    if(!m)
        return NULL;

    double **result = mcopy(m);
    if(!result)
        return NULL;

    if(mswapra(result, row_1, row_2))
    {
        mfree(result);
        return NULL;
    }

    return result;
}

mstatus_t mswapra(double **m, unsigned int row_1, unsigned int row_2)
{
    if(!m)
        return ME_NULL;

    matrix_t *matrix = M_ADDR(m);

    if(row_1 >= matrix->rows || row_2 >= matrix->rows)
        return ME_IINDEX;

    double *temp = m[row_1];
    m[row_1] = m[row_2];
    m[row_2] = temp;

    return MSUCCESS;
}

// TODO: swap cols

double **mmulm(const double **first, const double **second)
{
    if(!first || !second)
        return NULL;

    matrix_t *m1 = M_ADDR(first);
    matrix_t *m2 = M_ADDR(second);

    if(m1->cols != m2->rows)
        return NULL;

    double **result = matrix(m1->rows, m2->cols);
    if(!result)
        return NULL;

    unsigned int i = 0, j = 0, k = 0;
    while(i < m1->rows)
    {
        j = 0;
        while(j < m2->cols)
        {
            k = 0;
            while(k < m2->rows)
            {
                result[i][j] += first[i][k] * second[k][j];
                k++;
            }
            j++;
        }
        i++;
    }

    return result;
}

// mmulm -- matrix mul matrix assign
mstatus_t mmulma(double **dest, const double **second)
{
    if(!dest || !second)
        return ME_NULL;

    matrix_t *m1 = M_ADDR(dest);
    matrix_t *m2 = M_ADDR(second);

    if(m1->cols != m2->rows)
        return ME_ISIZE;

    unsigned int i = 0, j = 0, k = 0;
    double temp = 0.;
    while(i < m1->rows)
    {
        j = 0;
        while(j < m2->cols)
        {
            k = 0;
            temp = 0.;
            while(k < m2->rows)
            {
                temp += dest[i][k] * second[k][j];
                k++;
            }

            dest[i][j] = temp;
            j++;
        }
        i++;
    }

    return MSUCCESS;
}

// TODO: Gauss

double **mcopy(const double **raw)
{
    if(!raw)
        return NULL;

    matrix_t *m = M_ADDR(raw);
    double **copy = matrix(m->rows, m->cols);
    if(!copy)
        return NULL;

    unsigned int i = 0, j = 0;
    while(i < m->rows)
    {
        j = 0;
        while(j < m->cols)
        {
            copy[i][j] = raw[i][j];
            j++;
        }
        i++;
    }

    return copy;
}

void mprint(double **m)
{
    matrix_t *matrix = M_ADDR(m);

    for(unsigned i = 0; i < matrix->rows; ++i)
    {
        for(unsigned j = 0; j < matrix->cols; ++j)
            printf("%lf ", m[i][j]);
        putchar('\n');
    }
}
