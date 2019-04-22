#pragma once

#include <istream>
#include "token.hh"

namespace ast::parser
{
    class lexer
    {
    private:
        std::istream& input_;
        token current_token_;
        char current_value_;
    public:
        lexer(std::istream& input);

        token current();
        char value();
        void eat();

    private:
        void eat_escaped();
        void eat_character();
    };
}