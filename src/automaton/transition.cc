#include "automaton/transition.hh"

namespace automaton
{
    transition::transition(state* source, state* destination):
        source_{source},
        destination_{destination}
    {}

    state* transition::get_source()
    {
        return source_;
    }

    state* transition::get_destination()
    {
        return destination_;
    }
}