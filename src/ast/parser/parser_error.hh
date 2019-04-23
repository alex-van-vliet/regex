#pragma once

#include <stdexcept>

namespace ast::parser
{
    class parser_error: public std::runtime_error
    {
    public:
        explicit parser_error(const std::string& str): std::runtime_error{str}
        {}
    };
}
