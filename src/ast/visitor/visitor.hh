#pragma once

#include "forward.hh"

namespace ast::visitor
{
    class visitor
    {
    public:
        virtual void visit(ast::character& node) = 0;
    };
}