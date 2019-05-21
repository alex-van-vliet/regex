#include "automaton/graph.hh"

namespace automaton
{
    graph::graph():
        states_{},
        transitions_{},
        initial_states_{},
        final_states_{}
    {}

    const std::unordered_set<std::unique_ptr<state>>& graph::get_states() const
    {
        return states_;
    }

    state* graph::new_state()
    {
        return states_.insert(std::make_unique<state>()).first->get();
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
}