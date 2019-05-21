#pragma once

namespace automaton
{
    template <typename type, typename... types>
    transition* graph::new_transition(state* source, state* destination,
        types... args)
    {
        auto* transition = transitions_.insert(std::make_unique<type>(source,
            destination, std::forward<types>(args)...)).first->get();
        source->add_out_transition(state::internal(), transition);
        destination->add_in_transition(state::internal(), transition);
        return transition;
    }
}