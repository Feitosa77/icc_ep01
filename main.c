#include <math.h>  /* nextafter e INFINITY */
#include <float.h> /* DBL_MIN, DBL_MAX e DBL_EPSILON */
#include <stdio.h> /* printf */

/*
 * Intervalo Aberto
 * double a - MAIOR numero de maquina menor ou igual a x
 * double b - MENOR numero de maquina maior ou igual a x
 */

typedef struct IntervalReal IR;

struct IntervalReal { /* [a,b] */
    double a; /* max {a E R | a < x} */
    double b; /* min {b E R | b > x} */
};

void IR_init(IR *x, double val) {
    x->a = nextafter(val, DBL_MIN);
    x->b = nextafter(val, DBL_MAX);
}

void IR_sum(IR *x, IR y) { /* X := X + Y */
    x->a += y.a;
    x->b += y.b;
}

void IR_sub(IR *x, IR y) { /* X := X - Y */
    x->a -= y.b;
    x->b -= y.a;
}

/**************************************/
/* Implementacao ingenua */
#include <stdlib.h> /* qsort */

int cpmdouble(const void *d1, const void *d2) {
    return (*(double*) d1 > *(double*) d2 ? 1 : -1); 
}

void IR_mul(IR *x, IR y) { /* X := X * Y */
    double aux[4];

    aux[0] = x->a * y.a;
    aux[1] = x->a * y.b;
    aux[2] = x->b * y.a;
    aux[3] = x->b * y.b;

    qsort(&aux, 4, sizeof (double), cpmdouble);

    x->a = aux[0]; 
    x->b = aux[3];
}

void IR_div(IR *x, IR y) { /* X := X / Y */
    if (y.a > DBL_EPSILON || y.b > DBL_EPSILON) {
        y.a = 1/y.a;
        y.b = 1/y.b;
        IR_mul(x, y);
    }
    else {
        x->a = -INFINITY; 
        x->b = INFINITY;
    }
}

void IR_print(IR x) {
    double er = x.b-x.a;

    /* le os bytes na memoria como int 64bits */
    long long ulp = *(long long*)&x.b - *(long long*)&x.a;

    printf("[%1.8e,%1.8e]\n", x.a, x.b);
    printf("EA: %1.8e; ER: %1.8e; ULPS: %llu\n", er, er/x.a, ulp);
}

/**************************************/

#include <stdio.h>  /* fgets e printf */
#include <string.h> /* strtok */
#include <stdlib.h> /* atof */

#define B_SIZE 1024

char BUFFER[B_SIZE];

int main() {
    IR x, y;
    char *token, *op;
    int i = 0; /* Impressao */

    fgets(BUFFER, B_SIZE, stdin);

    token = strtok(BUFFER, " ");

    IR_init(&x, atof(token));

    printf("*****************\n");
    printf("[%llu,%llu]\n", *(long long*)&x.a, *(long long*)&x.b);
    printf("[%1.8e,%1.8e]\n", x.a, x.b);
    printf("*****************\n\n");

    IR_print(x);

    while (op = strtok(NULL, " ")) {
        token = strtok(NULL, " ");

        IR_init(&y, atof(token));

        printf("%d:\n", ++i);
        printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] = \n", x.a, x.b, *op, y.a, y.b);

        switch(*op) {
            case '+' : IR_sum(&x, y); break;
            case '-' : IR_sub(&x, y); break;
            case '*' : IR_mul(&x, y); break;
            case '/' : IR_div(&x, y); break;
            default  : printf("skip (%s)\n", op); break;
        }

        IR_print(x); putchar('\n');
    }

    return 0;
}

