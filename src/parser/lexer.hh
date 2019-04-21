#pragma once

#include <istream>
#include "token.hh"

namespace parser
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
    };
}