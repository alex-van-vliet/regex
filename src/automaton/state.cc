#pragma once

#include "automaton/state.hh"

namespace automaton
{
    state::state():
        in_transitions_{},
        out_transitions_{}
    {}
}
