#pragma once

#include "automaton/transition.hh"

namespace automaton::transitions
{
    class epsilon: public transition
    {
    public:
        epsilon(state* source, state* destination);
        bool accept(char c) override;
        ~epsilon() override = default;
    };
}