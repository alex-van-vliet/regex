#include "automaton/graph.hh"

namespace automaton
{
    graph::graph():
        states_{},
        transitions_{},
        initial_states_{},
        final_states_{}
    {}

    const graph::states_t& graph::get_states() const
    {
        return states_;
    }

    state* graph::new_state()
    {
        auto unique = std::make_unique<state>();
        auto address = unique.get();
        states_.insert({unique.get(), std::move(unique)});
        return address;
    }

    void graph::set_initial(automaton::state* state, bool initial)
    {
        if (initial)
            initial_states_.insert(state);
        else
            initial_states_.erase(state);
    }

    const std::unordered_set<state*>& graph::get_initial_states() const
    {
        return initial_states_;
    }

    void graph::set_final(automaton::state* state, bool final)
    {
        if (final)
            final_states_.insert(state);
        else
            final_states_.erase(state);
    }

    const std::unordered_set<state*>& graph::get_final_states() const
    {
        return final_states_;
    }

    const graph::transitions_t& graph::get_transitions() const
    {
        return transitions_;
    }
}