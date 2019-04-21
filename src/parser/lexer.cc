#include "lexer.hh"

namespace parser
{
    lexer::lexer(std::istream &input):
        input_{input},
        current_token_{token::BEGIN}
    {}

    token lexer::current()
    {
        return current_token_;
    }

    char lexer::value()
    {
        return '\0';
    }

    void lexer::eat()
    {
        current_token_ = token::END;
    }
}