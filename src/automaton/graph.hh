#pragma once

#include <unordered_set>
#include <memory>

#include "automaton/state.hh"
#include "automaton/transition.hh"

namespace automaton
{
    class graph
    {
    private:
        std::unordered_set<std::unique_ptr<state>> states_;
        std::unordered_set<std::unique_ptr<transition>> transitions_;

        std::unordered_set<state*> initial_states_;
        std::unordered_set<state*> final_states_;
    public:
        graph();
        void merge(graph& graph);

        state* new_state();
        void set_initial(state* state, bool initial);
        void set_final(state* state, bool final);

        const std::unordered_set<std::unique_ptr<state>>& get_states() const;
        const std::unordered_set<state*>& get_initial_states() const;
        const std::unordered_set<state*>& get_final_states() const;
    };
}
