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
    int ch, decimal = 0, type;

    memset(token, 0, MAX);

    ch = getchar();
    while (isspace(ch)) {
        ch = getchar();
    }

    if (ch == EOF) return END;

    if ((ch >= '0' && ch <= '9') || (ch == '.')) {
        while ((ch >= '0' && ch <= '9') || (ch == '.')) {
            if ((ch == '.') && (decimal != 0)) {
                return ERROR;
            }
            else if (decimal != 0) {
                decimal = 1;
            }

            if (index == MAX - 2) break;
            token[index++] = ch;
            ch = getchar();
        }

        ungetc(ch, stdin);
        return NUMBER;
    }

    type = ERROR;

    switch (ch) {
        case '+':
            type = PLUS;
            break;
        case '-':
            type = MINUS;
            break;
        case '*':
            type = MULT;
            break;
        case '/':
            type = DIV;
            break;
        case '%':
            type = REM;
            break;
        case '^':
            type = POW;
            break;
        case ':':
            ch = getchar();
            if (ch != EOF && ch == '=') {
                return ASSIGN;
            }
            break;
        default:
            break;
    }

    return type;
}


int main()
{
    int type = gettoken();

    while (type != ERROR && type != END) {
        printf("%d %s\n", type, token);
        type = gettoken();
    }

    return 0;
}

