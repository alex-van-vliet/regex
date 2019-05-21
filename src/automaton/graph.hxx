#pragma once

namespace automaton
{
    template <typename type, typename... types>
    transition* graph::new_transition(state* source, state* destination,
        types... args)
    {
        auto unique = std::make_unique<type>(source, destination,
            std::forward<types>(args)...);
        auto address = unique.get();
        transitions_.insert({unique.get(), std::move(unique)});
        source->add_out_transition(state::internal(), address);
        destination->add_in_transition(state::internal(), address);
        return address;
    }
}