#pragma once

#include "forward.hh"

namespace ast::visitor
{
    class visitor
    {
    public:
        void operator()(node* node);
        virtual void visit(character& node) = 0;
        virtual void visit(concatenation& node) = 0;
        virtual void visit(disjunction& node) = 0;
        virtual void visit(kleene& node) = 0;
    };
}