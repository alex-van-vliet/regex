#pragma once

#include "visitor.hh"

namespace parser::ast
{
    class node
    {
    public:
        virtual void accept(visitor::visitor& v) = 0;
        virtual ~node() = default;
    };
}
