#include "character.hh"

namespace ast
{
    character::character(char value): value_{value}
    {}

    void character::accept(visitor::visitor& v)
    {
        v.visit(*this);
    }

    char character::value()
    {
        return value_;
    }
}
