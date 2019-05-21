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
}