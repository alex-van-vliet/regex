#pragma once

#include "forward.hh"

namespace parser::visitor
{
    class visitor
    {
    public:
        virtual void visit(ast::character& node) = 0;
    };
}