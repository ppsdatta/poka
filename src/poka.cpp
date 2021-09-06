#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cstdio>

#define MAX 100

namespace parser
{
    enum class Token
    {
        EMPTY,
        NONE,
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
        CCURLY,
        COMMA
    };

    struct Lexer
    {
        std::string token;
        

        Lexer() : lasttoken{Token::EMPTY}, token{""}
        {}

        Token gettoken()
        {
            int ch, decimal = 0;
            Token type;

            token = "";

            ch = std::getchar();
            while (isspace(ch))
            {
                ch = std::getchar();
            }

            if (ch == EOF)
                return Token::END;

            if ((ch >= '0' && ch <= '9') || (ch == '.'))
            {
                while ((ch >= '0' && ch <= '9') || (ch == '.'))
                {
                    if (ch == '.')
                    {
                        if (decimal > 0)
                        {
                            /* Already found a decimal point */
                            return Token::ERROR;
                        }
                        else
                        {
                            decimal = 1;
                        }
                    }

                    token += ch;
                    ch = std::getchar();
                }

                ungetc(ch, stdin);
                return Token::NUMBER;
            }

            if (std::isalpha(ch))
            {
                while (std::isalpha(ch) || std::isdigit(ch) || ch == '_')
                {
                    token += ch;
                    ch = std::getchar();
                }

                ungetc(ch, stdin);
                return Token::SYM;
            }

            type = Token::ERROR;

            switch (ch)
            {
            case '+':
                type = Token::PLUS;
                break;
            case '-':
                type = Token::MINUS;
                break;
            case '*':
                type = Token::MULT;
                break;
            case '/':
                type = Token::DIV;
                break;
            case '%':
                type = Token::REM;
                break;
            case '^':
                type = Token::POW;
                break;
            case ':':
                ch = std::getchar();
                if (ch != EOF && ch == '=')
                {
                    type = Token::ASSIGN;
                }
                else
                {
                    ungetc(ch, stdin);
                    type = Token::COLON;
                }
                break;
            case ';':
                type = Token::SEMI;
                break;
            case '=':
                type = Token::EQ;
                break;
            case '<':
                ch = std::getchar();
                if (ch == '>')
                {
                    type = Token::NOT;
                }
                else if (ch == '=')
                {
                    type = Token::LE;
                }
                else
                {
                    type = Token::LT;
                    std::ungetc(ch, stdin);
                }
                break;
            case '>':
                ch = std::getchar();
                if (ch == '=')
                {
                    type = Token::GE;
                }
                else
                {
                    type = Token::GT;
                    ungetc(ch, stdin);
                }
                break;
            case '(':
                type = Token::OPAREN;
                break;
            case ')':
                type = Token::CPAREN;
                break;
            case '[':
                type = Token::OBRACKET;
                break;
            case ']':
                type = Token::CBRACKET;
                break;
            case '{':
                type = Token::OCURLY;
                break;
            case '}':
                type = Token::CCURLY;
                break;
            case ',':
                type = Token::COMMA;
                break;
            case EOF:
                type = Token::END;
                break;
            default:
                break;
            }

            return type;
        }

        Token nexttoken()
        {
            Token token;

            if (lasttoken == Token::EMPTY)
            {
                return gettoken();
            }
            else
            {
                token = lasttoken;
                lasttoken = Token::EMPTY;
                return token;
            }
        }

        void savetoken(Token tok)
        {
            lasttoken = tok;
        }
    private:
        Token lasttoken;
    };

}

int main()
{
    parser::Lexer lexer;

    parser::Token type = lexer.gettoken();

    while (type != parser::Token::ERROR && type != parser::Token::END)
    {
        std::printf("%d %s\n", type, lexer.token.c_str());
        type = lexer.gettoken();
    }

    if (type == parser::Token::ERROR)
    {
        std::puts("]]ERROR");
    }

    return 0;
}
