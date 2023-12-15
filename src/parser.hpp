#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <vector>

namespace parser
{

    struct program_head
    {
        std::string result;

        bool parse(Lexer lexer)
        {
            Token token = lexer.gettoken();
            if (token != Token::SYM)
                return false;
            if (lexer.token != "program")
                return false;

            // we got program symbol
            token = lexer.gettoken();
            if (token != Token::SYM)
                return false;

            result = lexer.token;

            // we got program name, next ';'

            token = lexer.gettoken();
            if (token != Token::SEMI)
                return false;

            return true;
        }
    };

    struct use_part
    {
        std::vector<std::string> result;

        bool parse(Lexer lexer)
        {
            Token token = lexer.gettoken();
            if (token != Token::SYM)
                return false;
            if (lexer.token != "use")
                return false;
            // use
            while (true)
            {
                token = lexer.gettoken();
                if (token != Token::SYM)
                    return false;

                result.push_back(lexer.token);

                token = lexer.gettoken();

                if (token == Token::SEMI)
                    break;
                if (token != Token::COMMA)
                    return false;
            }

            return true;
        }
    };
}
#endif