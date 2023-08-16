#ifndef IR_H
#define IR_H

#include <math.h>  /* nextafter e INFINITY */
#include <float.h> /* DBL_MIN, DBL_MAX e DBL_EPSILON */
#include <stdio.h> /* printf */
#include <stdlib.h> /* qsort */

/*
 * Intervalo Aberto
 * double a - MAIOR numero de maquina menor ou igual a x
 * double b - MENOR numero de maquina maior ou igual a x
 */

typedef struct IntervalReal IR;

struct IntervalReal { /* [a,b] */
    float a; /* max {a E R | a < x} */
    float b; /* min {b E R | b > x} */
};

void IR_init(IR *x, float val);

void IR_sum(IR *x, IR y); /* X := X + Y */

void IR_sub(IR *x, IR y); /* X := X - Y */

void IR_mul(IR *x, IR y); /* X := X * Y */

void IR_div(IR *x, IR y); /* X := X / Y */

void IR_print(IR x);

#endif

