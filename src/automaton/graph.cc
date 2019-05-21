#include "automaton/graph.hh"

namespace automaton
{
    graph::graph():
        states_{},
        transitions_{},
        initial_states_{},
        final_states_{}
    {}
}