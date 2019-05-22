#pragma once

#include "ast/visitor/visitor.hh"
#include "ast/visitor/alphabet_finder.hh"
#include "automaton/graph.hh"

namespace automaton::algorithms
{
    class thompson: public ast::visitor::visitor
    {
    private:
        const ast::visitor::alphabet_t& alphabet_;
        graph graph_;
    public:
        thompson(const ast::visitor::alphabet_t& alphabet);
        void visit(ast::character& node) override;
        void visit(ast::wildcard& node) override;
        void visit(ast::concatenation& node) override;
        void visit(ast::disjunction& node) override;
        void visit(ast::kleene& node) override;
        virtual ~thompson() = default;

        const graph& created_graph() const;
    };
}
