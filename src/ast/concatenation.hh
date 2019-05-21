#pragma once

#include "ast/node.hh"

namespace ast
{
    class concatenation: public node
    {
    private:
        node* left_;
        node* right_;
    public:
        concatenation(node* left, node* right);
        ~concatenation() override;
        void accept(visitor::visitor& v) override;
        node* left();
        node* right();
    };
}
