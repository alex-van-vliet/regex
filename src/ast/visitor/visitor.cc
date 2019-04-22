#include "visitor.hh"

#include "node.hh"

namespace ast::visitor
{
    void visitor::operator()(node* node)
    {
        node->accept(*this);
    }
}