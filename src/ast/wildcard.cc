#include "ast/wildcard.hh"

namespace ast
{
    wildcard::wildcard()
    {}

    void wildcard::accept(visitor::visitor& v)
    {
        v.visit(*this);
    }
}
