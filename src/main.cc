#include <iostream>
#include "lexer.hh"
#include "parser.hh"
#include "prettyprinter.hh"

int main()
{
    auto lexer = ast::parser::lexer(std::cin);
    auto parser = ast::parser::parser(lexer);
    auto* ast = parser.parse();
    auto printer = ast::visitor::prettyprinter(std::cout);
    ast->accept(printer);
    delete ast;
    return 0;
}