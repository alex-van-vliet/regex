#pragma once

#include "ast/node.hh"

namespace ast
{
    class kleene: public node
    {
    private:
        node* left_;
    public:
        kleene(node* left);
        ~kleene() override;
        void accept(visitor::visitor& v) override;
        node* left();
    };
}
