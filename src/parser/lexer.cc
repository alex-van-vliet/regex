#include "lexer.hh"

namespace parser
{
    lexer::lexer(std::istream &input):
        input_{input},
        current_token_{token::BEGIN},
        current_value_{'\0'}
    {}

    token lexer::current()
    {
        return current_token_;
    }

    char lexer::value()
    {
        return current_value_;
    }

    void lexer::eat()
    {
        if (current_token_ == token::END
            || !(input_ >> current_value_)) {
            current_value_ = '\0';
            current_token_ = token::END;
            return;
        }
        if (current_value_ == '.')
            current_token_ = token::DOT;
        else if (current_value_ == '*')
            current_token_ = token::STAR;
        else
            current_token_ = token::OPENING_PARENTHESIS;
    }
}