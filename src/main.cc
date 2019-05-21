#include <iostream>
#include "lexer.hh"
#include "parser.hh"
#include "prettyprinter.hh"
#include "alphabet_finder.hh"

int main()
{
    auto lexer = ast::parser::lexer(std::cin);
    auto parser = ast::parser::parser(lexer);
    auto* ast = parser.parse();

    auto printer = ast::visitor::prettyprinter(std::cout);
    printer(ast);

    auto alphabet_finder = ast::visitor::alphabet_finder();
    alphabet_finder(ast);

    std::cout << std::endl << "Letters: ";
    for (char it : alphabet_finder.letters())
        std::cout << it;
    std::cout << std::endl;
    delete ast;
    return 0;
}