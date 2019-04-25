#pragma once

#include "node.hh"

namespace ast
{
    class wildcard : public node
    {
    public:
        explicit wildcard();
        ~wildcard() override = default;
        void accept(visitor::visitor& v) override;
    };
}