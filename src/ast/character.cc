#include "character.hh"

namespace ast
{
    character::character(char value): value_{value}
    {}

    void character::accept(visitor::visitor& v)
    {
    }

    char character::value()
    {
        return value_;
    }
}
