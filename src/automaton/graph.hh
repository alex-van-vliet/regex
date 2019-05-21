#pragma once

#include <unordered_set>
#include <unordered_map>
#include <memory>

#include "automaton/state.hh"
#include "automaton/transition.hh"

namespace automaton
{
    class graph
    {
    public:
        using states_t = std::unordered_map<state*, std::unique_ptr<state>>;
        using transitions_t = std::unordered_map<transition*,
            std::unique_ptr<transition>>;
    private:
        states_t states_;
        transitions_t transitions_;

        std::unordered_set<state*> initial_states_;
        std::unordered_set<state*> final_states_;
    public:
        graph();
        void merge(graph& graph);

        state* new_state();
        void set_initial(state* state, bool initial);
        void set_final(state* state, bool final);

        template <typename type, typename... types>
        transition* new_transition(state* source, state* destination,
            types... args);

        const states_t& get_states() const;
        const std::unordered_set<state*>& get_initial_states() const;
        const std::unordered_set<state*>& get_final_states() const;

        const transitions_t&
            get_transitions() const;
    };
}

#include "graph.hxx"
