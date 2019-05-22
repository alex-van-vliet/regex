#pragma once

#include "automaton/transition.hh"

namespace automaton::transitions
{
    class letter: public transition
    {
    private:
        char letter_;
    public:
        letter(state* source, state* destination, char l);
        bool accept(char c) override;
        char get_letter() const;
        ~letter() override = default;
    };
}