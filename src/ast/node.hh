#pragma once

#include "ast/visitor/visitor.hh"

namespace ast
{
    class node
    {
    public:
        virtual void accept(visitor::visitor& v) = 0;
        virtual ~node() = default;
    };
}
