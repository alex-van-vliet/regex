#pragma once

#include <ostream>
#include "visitor.hh"

namespace ast::visitor
{
    class prettyprinter: public visitor
    {
    private:
        std::ostream& output_;
    public:
        prettyprinter(std::ostream& output);
        void visit(character& node) override;
        void visit(concatenation& node) override;
        void visit(disjunction& node) override;
        void visit(kleene& node) override;
    };
}

