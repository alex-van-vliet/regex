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
        void operator()(node* node) override ;
        void visit(character& node) override;
    };
}

