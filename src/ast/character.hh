#pragma once

#include "ast/node.hh"

namespace ast
{
    class character : public node
    {
    private:
        char value_;
    public:
        explicit character(char value);
        ~character() override = default;
        void accept(visitor::visitor& v) override;
        char value();
    };
}
