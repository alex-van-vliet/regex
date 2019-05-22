#include "automaton/transitions/letter.hh"

namespace automaton::transitions
{
    letter::letter(state* source, state* destination, char l):
        transition(source,destination),
        letter_{l}
    {}

    bool letter::accept(char c)
    {
        return c == letter_;
    }

    char letter::get_letter() const
    {
        return letter_;
    }
}