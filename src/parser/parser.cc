#include "parser.hh"

#include "character.hh"

namespace parser
{
    parser::parser(lexer& lexer): lexer_{lexer}
    {
    }

    ast::node* parser::parse()
    {
        lexer_.eat();
        return new ast::character(lexer_.value());
    }
}
