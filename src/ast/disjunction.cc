#include "ast/disjunction.hh"

namespace ast
{
    disjunction::disjunction(node* left, node* right):
        left_{left},
        right_{right}
    {}

    disjunction::~disjunction()
    {
        delete left_;
        delete right_;
    }

    void disjunction::accept(visitor::visitor& v)
    {
        v.visit(*this);
    }

    node* disjunction::left()
    {
        return left_;
    }

    node* disjunction::right()
    {
        return right_;
    }
}