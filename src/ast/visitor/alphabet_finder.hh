#pragma once

#include <unordered_set>
#include "visitor.hh"

namespace ast::visitor
{
    class alphabet_finder: public visitor
    {
    private:
        std::unordered_set<char> letters_;
    public:
        alphabet_finder();
        void visit(character& node) override;
        void visit(wildcard& node) override;
        void visit(concatenation& node) override;
        void visit(disjunction& node) override;
        void visit(kleene& node) override;
        virtual ~alphabet_finder() = default;

        const std::unordered_set<char>& letters() const;
    };
}
