#include "prettyprinter.hh"
#include "character.hh"

namespace ast::visitor
{
    prettyprinter::prettyprinter(std::ostream& output): output_{output}
    {}

    void prettyprinter::operator()(ast::node* node)
    {
        node->accept(*this);
    }

    void prettyprinter::visit(character& node)
    {
        output_ << node.value();
    }
}
