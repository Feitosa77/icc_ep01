#include <stdio.h>  /* fgets e printf *///
#include <string.h> /* strtok */
#include <stdlib.h> /* strtof *///
#include "IR.h"

#define B_SIZE 1024

char BUFFER[B_SIZE];

int main() {
    IR x, y;
    char *token, *op;
    int i = 0; /* Impressao */

    fgets(BUFFER, B_SIZE, stdin);

    token = strtok(BUFFER, " ");

    IR_init(&x, strtof(token, NULL));

    while (op = strtok(NULL, " ")) {
        token = strtok(NULL, " ");

        IR_init(&y, strtof(token, NULL));

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

