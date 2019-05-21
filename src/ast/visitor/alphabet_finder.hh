#pragma once

#include <unordered_set>
#include "ast/visitor/visitor.hh"

namespace ast::visitor
{
    using alphabet_t = std::unordered_set<char>;

    class alphabet_finder: public visitor
    {
    private:
        alphabet_t letters_;
    public:
        alphabet_finder();
        void visit(character& node) override;
        void visit(wildcard& node) override;
        void visit(concatenation& node) override;
        void visit(disjunction& node) override;
        void visit(kleene& node) override;
        virtual ~alphabet_finder() = default;

        const alphabet_t& letters() const;
    };
}
