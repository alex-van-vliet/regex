#include "prettyprinter.hh"
#include "character.hh"
#include "concatenation.hh"

namespace ast::visitor
{
    prettyprinter::prettyprinter(std::ostream& output): output_{output}
    {}

    void prettyprinter::operator()(node* node)
    {
        node->accept(*this);
    }

    void prettyprinter::visit(character& node)
    {
        output_ << node.value();
    }

    void prettyprinter::visit(ast::concatenation& node)
    {
        (*this)(node.left());
        (*this)(node.right());
    }
}
