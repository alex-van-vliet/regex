#pragma once

#include "lexer.hh"
#include "forward.hh"
#include "node.hh"

namespace parser
{
    class parser
    {
    private:
        lexer& lexer_;
    public:
        parser(lexer& lexer);
        ast::node* parse();
    };
}
