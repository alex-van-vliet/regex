#include "visitor.hh"

#include "ast/node.hh"

namespace ast::visitor
{
    void visitor::operator()(node* node)
    {
        node->accept(*this);
    }
}