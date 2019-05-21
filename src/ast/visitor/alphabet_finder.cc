#include "ast/visitor/alphabet_finder.hh"
#include "ast/character.hh"
#include "ast/concatenation.hh"
#include "ast/disjunction.hh"
#include "ast/kleene.hh"
#include "ast/wildcard.hh"

namespace ast::visitor
{
    alphabet_finder::alphabet_finder():
        letters_{}
    {}

    void alphabet_finder::visit(character& node)
    {
        letters_.insert(node.value());
    }

    void alphabet_finder::visit([[maybe_unused]] wildcard& node)
    {
    }

    void alphabet_finder::visit(concatenation& node)
    {
        (*this)(node.left());
        (*this)(node.right());
    }

    void alphabet_finder::visit(disjunction& node)
    {
        (*this)(node.left());
        (*this)(node.right());
    }

    void alphabet_finder::visit(kleene& node)
    {
        (*this)(node.left());
    }

    const alphabet_t& alphabet_finder::letters() const
    {
        return letters_;
    }
}
