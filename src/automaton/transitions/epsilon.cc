#include "automaton/transitions/epsilon.hh"

namespace automaton::transitions
{
    epsilon::epsilon(state* source, state* destination):
        transition(source,destination)
    {}

    bool epsilon::accept([[maybe_unused]] char c)
    {
        return true;
    }
}