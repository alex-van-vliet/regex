#pragma once

#include "forward.hh"

namespace automaton
{
    class transition
    {
    private:
        state* source_;
        state* destination_;

    public:
        transition(state* source, state* destination);

        state* get_source();
        state* get_destination();

        virtual bool accept(char c) = 0;
        virtual ~transition() = default;
    };
}
