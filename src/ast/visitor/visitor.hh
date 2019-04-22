#pragma once

#include "forward.hh"

namespace ast::visitor
{
    class visitor
    {
    public:
        virtual void operator()(node* node) = 0;
        virtual void visit(character& node) = 0;
        virtual void visit(concatenation& node) = 0;
    };
}