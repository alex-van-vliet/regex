#include "alphabet_finder.hh"
#include "character.hh"
#include "concatenation.hh"
#include "disjunction.hh"
#include "kleene.hh"
#include "wildcard.hh"

namespace ast::visitor
{
    alphabet_finder::alphabet_finder():
        letters_{std::unordered_set<char>()}
    {}

    void alphabet_finder::visit(character& node)
    {
        letters_.insert(node.value());
    }

    void alphabet_finder::visit(wildcard& node)
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

    const std::unordered_set<char>& alphabet_finder::letters() const
    {
        return letters_;
    }
}
