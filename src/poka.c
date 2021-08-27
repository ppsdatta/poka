#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

enum
{
    END,
    ERROR,
    NUMBER,
    PLUS,
    MINUS,
    MULT,
    DIV,
    REM,
    POW,
    ASSIGN,
    SYM,
    SEMI,
    COLON,
    EQ,
    LT,
    GT,
    NOT,
    LE,
    GE,
    OPAREN,
    CPAREN,
    OBRACKET,
    CBRACKET,
    OCURLY,
    CCURLY
};

static char token[MAX];

int gettoken(void)
{
    int index = 0;
    int ch, decimal = 0, type;

    memset(token, 0, MAX);

    ch = getchar();
    while (isspace(ch))
    {
        ch = getchar();
    }

    if (ch == EOF)
        return END;

    if ((ch >= '0' && ch <= '9') || (ch == '.'))
    {
        while ((ch >= '0' && ch <= '9') || (ch == '.'))
        {
            if ((ch == '.') && (decimal != 0))
            {
                return ERROR;
            }
            else if (decimal != 0)
            {
                decimal = 1;
            }

            if (index == MAX - 2)
                break;
            token[index++] = ch;
            ch = getchar();
        }

        ungetc(ch, stdin);
        return NUMBER;
    }

    if (isalpha(ch))
    {
        while (isalpha(ch) || isdigit(ch) || ch == '_')
        {
            if (index == MAX - 2)
                break;
            token[index++] = ch;
            ch = getchar();
        }

        ungetc(ch, stdin);
        return SYM;
    }

    type = ERROR;

    switch (ch)
    {
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
        if (ch != EOF && ch == '=')
        {
            type = ASSIGN;
        }
        else
        {
            ungetc(ch, stdin);
            type = COLON;
        }
        break;
    case ';':
        type = SEMI;
        break;
    case '=':
        type = EQ;
        break;
    case '<':
        ch = getchar();
        if (ch == '>')
        {
            type = NOT;
        }
        else if (ch == '=')
        {
            type = LE;
        }
        else
        {
            type = LT;
            ungetc(ch, stdin);
        }
        break;
    case '>':
        ch = getchar();
        if (ch == '=')
        {
            type = GE;
        }
        else
        {
            type = GT;
            ungetc(ch, stdin);
        }
        break;
    case '(':
        type = OPAREN;
        break;
    case ')':
        type = CPAREN;
        break;
    case '[':
        type = OBRACKET;
        break;
    case ']':
        type = CBRACKET;
        break;
    case '{':
        type = OCURLY;
        break;
    case '}':
        type = CCURLY;
        break;
    default:
        break;
    }

    return type;
}

static int lasttoken = -1;

int nexttoken(void)
{
    int token;

    if (lasttoken == -1)
    {
        return gettoken();
    }
    else
    {
        token = lasttoken;
        lasttoken = -1;
        return token;
    }
}

void savetoken(int tok)
{
    lasttoken = tok;
}

int main()
{
    int type = gettoken();

    while (type != ERROR && type != END)
    {
        printf("%d %s\n", type, token);
        type = gettoken();
    }

    return 0;
}
