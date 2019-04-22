#pragma once

#include "lexer.hh"
#include "forward.hh"
#include "node.hh"

namespace ast::parser
{
    class parser
    {
    private:
        lexer& lexer_;
    public:
        parser(lexer& lexer);
        node* parse();
    private:
        node* parse_disjunction();
        node* parse_concatenation();
        node* parse_expression();
    };
}
