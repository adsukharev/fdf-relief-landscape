#ifndef MASI_MATRIX_T_H
#define MASI_MATRIX_T_H

#include <stddef.h> // For NULL
#include <stdlib.h> // For malloc

#include "byte.h"

typedef enum matrix_status
{
    MSUCCESS = 0,
    ME_NULL,
    ME_ISIZE,
    ME_IINDEX
} mstatus_t;

// zero matrix
double **matrix(unsigned int rows, unsigned int cols);

// imatrix -- identity matrix
double **imatrix(unsigned int size);

// dmatrix -- diagonal matrix
double **dmatrix(unsigned int size, double diagonal_value);

// vfmatrix -- value filled matrix
double **vfmatrix(unsigned int rows, unsigned int cols, double value);

unsigned int mrows(double **);

unsigned int mcols(double **);

void mfree(double **);

// madd -- matrix add
double **madd(const double **, const double **);

// madda -- matrix add assign
mstatus_t madda(double **dest, const double **);

// mmuld -- matrix mul double
double **mmuld(const double **, double);

// mmulda -- matrix mul double assign
mstatus_t mmulda(double **, double);

// mmulrd -- matrix mul row double
double **mmulrd(const double **, unsigned int row, double);

// mmulrda -- matrix mul row double assign
mstatus_t mmulrda(double **, unsigned int row, double);

// mmulcd -- matrix mul col double
double **mmulcd(const double **, unsigned int col, double);

// mmulcda -- matrix mul col double assign
mstatus_t mmulcda(double **, unsigned int col, double);

// mswapr -- matrix swap rows
double **mswapr(const double **, unsigned int row_1, unsigned int row_2);

// mswapr -- matrix swap rows assign
mstatus_t mswapra(double **, unsigned int row_1, unsigned int row_2);

// TODO: swap cols

// mmulm -- matrix mul matrix
double **mmulm(const double **, const double **);

// mmulm -- matrix mul matrix assign
mstatus_t mmulma(double **dest, const double **);

// TODO: Gauss

double **mcopy(const double **);

void mprint(double **);

#endif // MASI_MATRIX_T_H