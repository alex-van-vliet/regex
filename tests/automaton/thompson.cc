#include <sstream>
#include <catch.hpp>
#include <algorithm>
#include <automaton/transitions/epsilon.hh>
#include "ast/parser/parser.hh"
#include "ast/character.hh"
#include "ast/concatenation.hh"
#include "ast/disjunction.hh"
#include "ast/kleene.hh"
#include "ast/wildcard.hh"
#include "ast/parser/parser_error.hh"
#include "ast/parser/lexer_error.hh"
#include "ast/visitor/alphabet_finder.hh"
#include "automaton/algorithms/thompson.hh"
#include "automaton/transitions/letter.hh"

bool are_graphs_similar(const automaton::graph& g1, const automaton::graph& g2);

SCENARIO("Thompson can transform the AST into a graph", "[thompson]")
{
    GIVEN("A parser with its a lexer") {
        auto input = std::stringstream();
        auto lexer = ast::parser::lexer(input);
        auto parser = ast::parser::parser(lexer);
        auto alphabet = ast::visitor::alphabet_finder();
        auto thompson = automaton::algorithms::thompson(alphabet.letters());
        WHEN("The ast is a character")
        {
            input << "t";
            ast::node* node = parser.parse();
            alphabet(node);
            thompson(node);

            automaton::graph expected;
            automaton::state* expected_source = expected.new_state();
            expected.set_initial(expected_source, true);
            automaton::state* expected_destination = expected.new_state();
            expected.set_final(expected_destination, true);
            expected.new_transition<automaton::transitions::letter>(expected_source,
                expected_destination, 't');

            REQUIRE(are_graphs_similar(expected, thompson.created_graph()));
        }
    }
}


bool are_initials_equal(const automaton::graph& g1, std::unordered_map<automaton::state*, int> g1_states,
    const automaton::graph& g2, std::vector<automaton::state*> g2_states)
{
    for (const auto& s1 : g1.get_initial_states())
    {
        const auto& ite = g1_states.find(s1);
        const auto& s2 = g2_states[ite->second];
        if (g2.get_initial_states().find(s2) == g2.get_initial_states().end())
            return false;
    }
    return true;
}

bool are_finals_equal(const automaton::graph& g1, std::unordered_map<automaton::state*, int> g1_states,
    const automaton::graph& g2, std::vector<automaton::state*> g2_states)
{
    for (const auto& s1 : g1.get_final_states())
    {
        const auto& ite = g1_states.find(s1);
        const auto& s2 = g2_states[ite->second];
        if (g2.get_final_states().find(s2) == g2.get_final_states().end())
            return false;
    }
    return true;
}

bool are_states_equal(const automaton::graph& g1,
    std::unordered_map<automaton::state*, int> g1_states,
    automaton::state* s1,
    const automaton::graph& g2,
    std::vector<automaton::state*> g2_states,
    automaton::state* s2,
    std::unordered_set<automaton::state*>& visited)
{
    if (visited.find(s1) != visited.end())
        return true;
    visited.insert(s1);
    if (s1->get_in_transitions().size() != s2->get_in_transitions().size())
        return false;
    for (auto t1 : s1->get_out_transitions())
    {
        if (t1->get_source() != s1)
            return false;
        auto d1 = t1->get_destination();
        auto ite = g1_states.find(d1);
        auto d2 = g2_states[ite->second];
        bool found = false;
        for (auto t2 : s2->get_out_transitions())
        {
            if (t2->get_source() == s2 && t2->get_destination() == d2)
            {
                found = true;
                if (dynamic_cast<automaton::transitions::epsilon*>(t1)
                    && dynamic_cast<automaton::transitions::epsilon*>(t2))
                {
                    if (!are_states_equal(g1, g1_states, d1,
                        g2, g2_states, d2, visited))
                        return false;
                }
                else if (dynamic_cast<automaton::transitions::letter*>(t1)
                         && dynamic_cast<automaton::transitions::letter*>(t2))
                {
                    auto tl1 = dynamic_cast<automaton::transitions::letter*>(t1);
                    auto tl2 = dynamic_cast<automaton::transitions::letter*>(t2);
                    if (tl1->get_letter() != tl2->get_letter())
                        return false;
                    if (!are_states_equal(g1, g1_states, d1,
                        g2, g2_states, d2, visited))
                        return false;
                }
                else
                {
                    return false;
                }
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

bool are_graphs_equal(const automaton::graph& g1,
    std::unordered_map<automaton::state*, int> g1_states,
    const std::unordered_set<automaton::state*>& g1_check_states,
    const automaton::graph& g2,
    std::vector<automaton::state*> g2_states,
    const std::unordered_set<automaton::state*>& g2_check_states,
    std::unordered_set<automaton::state*>& visited)
{
    if (g1_check_states.size() != g2_check_states.size())
        return false;
    for (const auto& s1 : g1_check_states)
    {
        auto ite = g1_states.find(s1);
        const auto& s2 = g2_states[ite->second];
        if (g2_check_states.find(s2) == g2_check_states.end())
            return false;
        if (!are_states_equal(g1, g1_states, s1,
            g2, g2_states, s2, visited))
            return false;
    }
    return true;
}

bool are_graphs_isomorphisms(const automaton::graph& g1, const automaton::graph& g2)
{
    std::unordered_map<automaton::state*, int> g1_states;
    int i = -1;
    for (const auto& s : g1.get_states())
        g1_states.insert({s.first, ++i});
    std::vector<automaton::state*> g2_states;
    for (const auto& s : g2.get_states())
        g2_states.push_back(s.first);
    std::sort(g2_states.begin(), g2_states.end());
    do {
        std::unordered_set<automaton::state*> visited;
        if (are_initials_equal(g1, g1_states, g2, g2_states)
            && are_finals_equal(g1, g1_states, g2, g2_states)
            && are_graphs_equal(g1, g1_states, g1.get_initial_states(),
            g2, g2_states, g2.get_initial_states(), visited))
            return true;
    } while (std::next_permutation(g2_states.begin(), g2_states.end()));

    return false;
}

bool are_graphs_similar(const automaton::graph& g1, const automaton::graph& g2)
{
    if (g1.get_states().size() != g2.get_states().size())
        return false;
    if (g1.get_initial_states().size() != g2.get_initial_states().size())
        return false;
    if (g1.get_final_states().size() != g2.get_final_states().size())
        return false;
    if (g1.get_transitions().size() != g2.get_transitions().size())
        return false;
    return are_graphs_isomorphisms(g1, g2);
}