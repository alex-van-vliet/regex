#include "prettyprinter.hh"
#include "character.hh"
#include "concatenation.hh"
#include "disjunction.hh"
#include "kleene.hh"

namespace ast::visitor
{
    prettyprinter::prettyprinter(std::ostream& output):
        output_{output}
    {}

    void prettyprinter::visit(character& node)
    {
        output_ << node.value();
    }

    void prettyprinter::visit(concatenation& node)
    {
        disjunction* left_is_disjunction = dynamic_cast<disjunction*>(node.left());
        if (left_is_disjunction) {
            output_ << '(';
            (*this)(node.left());
            output_ << ')';
        } else {
            (*this)(node.left());
        }
        disjunction* right_is_disjunction = dynamic_cast<disjunction*>(node.right());
        if (right_is_disjunction) {
            output_ << '(';
            (*this)(node.right());
            output_ << ')';
        } else {
            (*this)(node.right());
        }
    }

    void prettyprinter::visit(disjunction& node)
    {
        (*this)(node.left());
        output_ << '|';
        (*this)(node.right());
    }

    void prettyprinter::visit(kleene& node)
    {
        disjunction* left_is_disjunction = dynamic_cast<disjunction*>(node.left());
        if (left_is_disjunction) {
            output_ << '(';
            (*this)(node.left());
            output_ << ')';
        } else {
            concatenation* left_is_concatenation = dynamic_cast<concatenation*>(node.left());
            if (left_is_concatenation) {
                output_ << '(';
                (*this)(node.left());
                output_ << ')';
            } else {
                (*this)(node.left());
            }
        }
        output_ << '*';
    }
}
