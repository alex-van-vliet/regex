#include "lexer.hh"

namespace parser
{
    lexer::lexer(std::istream &input):
        input_{input}
    {}

    token lexer::current()
    {
        return token::BEGIN;
    }

    char lexer::value()
    {
        return '\0';
    }
}