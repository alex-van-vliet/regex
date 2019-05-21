#pragma once

#include <vector>
#include "automaton/forward.hh"

namespace automaton
{
    class state
    {
    private:
        std::vector<transition*> in_transitions_;
        std::vector<transition*> out_transitions_;
    public:
        state();

        void add_in_transition(transition* transition);
        void add_out_transition(transition* transition);

        const std::vector<transition*>& get_in_transitions();
        const std::vector<transition*>& get_out_transitions();
    };
}
