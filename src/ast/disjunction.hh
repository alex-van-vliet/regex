#pragma once

#include "node.hh"

namespace ast
{
    class disjunction: public node
    {
    private:
        node* left_;
        node* right_;
    public:
        disjunction(node* left, node* right);
        ~disjunction() override;
        void accept(visitor::visitor& v) override;
        node* left();
        node* right();
    };
}
