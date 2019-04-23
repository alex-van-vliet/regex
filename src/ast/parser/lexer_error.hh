#pragma once

#include <stdexcept>

namespace ast::parser
{
    class lexer_error: public std::runtime_error
    {
    public:
        explicit lexer_error(const std::string& str): std::runtime_error{str}
        {}
    };
}
