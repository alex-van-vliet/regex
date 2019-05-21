#pragma once

#include "ast/parser/lexer.hh"
#include "ast/forward.hh"
#include "ast/node.hh"

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
        node* parse_kleene();
        node* parse_disjunction();
        node* parse_concatenation();
        node* parse_expression();
    };
}
