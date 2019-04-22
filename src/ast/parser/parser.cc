#include "parser.hh"

#include "character.hh"

namespace ast::parser
{
    parser::parser(lexer& lexer): lexer_{lexer}
    {
    }

    node* parser::parse()
    {
        lexer_.eat();
        return new character(lexer_.value());
    }
}
