#include "prettyprinter.hh"
#include "character.hh"
#include "concatenation.hh"
#include "disjunction.hh"
#include "kleene.hh"

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

    void prettyprinter::visit(disjunction& node)
    {
        (*this)(node.left());
        output_ << '|';
        (*this)(node.right());
    }

    void prettyprinter::visit(kleene& node)
    {
        (*this)(node.left());
        output_ << '*';
    }
}
