#include "ast/kleene.hh"

namespace ast
{
    kleene::kleene(node* left):
        left_{left}
    {}

    kleene::~kleene()
    {
        delete left_;
    }

    void kleene::accept(visitor::visitor& v)
    {
        v.visit(*this);
    }

    node* kleene::left()
    {
        return left_;
    }
}