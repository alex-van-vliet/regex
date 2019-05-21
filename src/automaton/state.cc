#pragma once

#include "automaton/state.hh"

namespace automaton
{
    state::state():
        in_transitions_{},
        out_transitions_{}
    {}

    void state::add_in_transition(internal, transition* transition)
    {
        in_transitions_.push_back(transition);
    }

    void state::add_out_transition(internal, transition* transition)
    {
        out_transitions_.push_back(transition);
    }

    const std::vector<transition*>& state::get_in_transitions()
    {
        return in_transitions_;
    }

    const std::vector<transition*>& state::get_out_transitions()
    {
        return out_transitions_;
    }
}
