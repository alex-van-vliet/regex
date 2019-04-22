#include "prettyprinter.hh"
#include "character.hh"
#include "concatenation.hh"

namespace ast::visitor
{
    prettyprinter::prettyprinter(std::ostream& output): output_{output}
    {}

    void prettyprinter::visit(character& node)
    {
        output_ << node.value();
    }

    void prettyprinter::visit(concatenation& node)
    {
        (*this)(node.left());
        (*this)(node.right());
    }
}
