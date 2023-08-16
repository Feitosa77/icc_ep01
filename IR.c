#include "IR.h"

void IR_init(IR *x, float val) {
    x->a = nextafterf(val, FLT_MIN);
    x->b = nextafterf(val, FLT_MAX);
}

void IR_sum(IR *x, IR y) { /* X := X + Y */
    x->a += y.a;
    x->b += y.b;
}

void IR_sub(IR *x, IR y) { /* X := X - Y */
    x->a -= y.b;
    x->b -= y.a;
}

int cpmdouble(const void *d1, const void *d2) {
    return (*(float*) d1 > *(float*) d2 ? 1 : -1); 
}

void IR_mul(IR *x, IR y) { /* X := X * Y */
    float aux[4];

    aux[0] = x->a * y.a;
    aux[1] = x->a * y.b;
    aux[2] = x->b * y.a;
    aux[3] = x->b * y.b;

    qsort(&aux, 4, sizeof (float), cpmdouble);

    x->a = aux[0]; 
    x->b = aux[3];
}

void IR_div(IR *x, IR y) { /* X := X / Y */
    if (y.a > FLT_EPSILON || y.b > FLT_EPSILON) {
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
    float er = x.b-x.a;

    /* le os bytes na memoria como int 32bits */
    long ulp = *(int*)&x.b - *(int*)&x.a;

    printf("[%1.8e,%1.8e]\n", x.a, x.b);
    printf("EA: %1.8e; ER: %1.8e; ULPS: %lu\n", er, er/x.a, ulp);
}

