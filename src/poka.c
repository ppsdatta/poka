#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>


#define MAX 100
enum {
    END,
    ERROR, 
    NUMBER, 
    PLUS,
    MINUS,
    MULT,
    DIV,
    REM,
    POW,
    ASSIGN
};


static char token[MAX];

int gettoken(void)
{
    int index = 0;
    int ch, decimal = 0;

    memset(token, 0, MAX);
    while ((ch = getchar()) != EOF && (ch == ' ' || ch == '\t'))
        ;

    if (ch == EOF) return END;

    if ((ch >= '0' && ch <= '9') || (ch == '.')) {
        while ((ch >= '0' && ch <= '9') || (ch == '.')) {
            if ((ch == '.') && (decimal != 0)) {
                return ERROR;
            }
            else if (decimal != 0) {
                decimal = 1;
            }
            token[index++] = ch;
            ch = getchar();
        }

        if (ch != EOF) token[index++] = ch;

        putc(ch, stdin);
        token[index - 1] = '\0';

        return NUMBER;
    }

    switch (ch) {
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return MULT;
        case '/':
            return DIV;
        case '%':
            return REM;
        case '^':
            return POW;
        default:
            break;
    }

    putc(ch, stdin);
    return ERROR;
}


int main()
{
    int type = gettoken();
    printf("%d %s\n", type, token);
    return 0;
}

