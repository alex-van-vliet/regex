#include "ast/concatenation.hh"

namespace ast
{
    concatenation::concatenation(node* left, node* right):
        left_{left},
        right_{right}
    {}

    concatenation::~concatenation()
    {
        delete left_;
        delete right_;
    }

    void concatenation::accept(visitor::visitor& v)
    {
        v.visit(*this);
    }

    node* concatenation::left()
    {
        return left_;
    }

    node* concatenation::right()
    {
        return right_;
    }
}