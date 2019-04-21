#pragma once

#include <istream>
#include "token.hh"

namespace parser
{
    class lexer
    {
    private:
        std::istream& input_;
    public:
        lexer(std::istream& input);

        token current();
        char value();
        void eat();
    };
}