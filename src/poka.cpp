#include <iostream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"

int main()
{
    parser::Lexer lexer;
    parser::program_head phead;
    parser::use_part upart;

    // auto show_vec = [](const auto &v)
    // {
    //     for (auto e : v)
    //     {
    //         std::cout << e << "\n";
    //     }
    // };

    // if (upart.parse(lexer))
    // {
    //     std::cout << "Modules: << ";
    //     show_vec(upart.result);
    //     std::cout << ">> \n";
    // }
    // else
    // {
    //     std::cerr << "Cannot parse program\n";
    // }
}
