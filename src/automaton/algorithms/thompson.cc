#include "automaton/algorithms/thompson.hh"

#include "ast/character.hh"
#include "automaton/transitions/letter.hh"

namespace automaton::algorithms
{
    thompson::thompson(const ast::visitor::alphabet_t& alphabet):
        alphabet_{alphabet},
        graph_{}
    {}

    void thompson::visit(ast::character& node)
    {
        graph_ = graph();
        state* from = graph_.new_state();
        graph_.set_initial(from, true);
        state* to = graph_.new_state();
        graph_.set_final(to, true);
        graph_.new_transition<transitions::letter>(from, to, node.value());
    }

    void thompson::visit([[maybe_unused]] ast::wildcard& node)
    {}

    void thompson::visit([[maybe_unused]] ast::concatenation& node)
    {}

    void thompson::visit([[maybe_unused]] ast::disjunction& node)
    {}

    void thompson::visit([[maybe_unused]] ast::kleene& node)
    {}

    const graph& thompson::created_graph() const
    {
        return graph_;
    }
}