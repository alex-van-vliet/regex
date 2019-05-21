#include <sstream>
#include <catch.hpp>
#include "automaton/graph.hh"

SCENARIO("The graph can link states with transitions", "[graph]")
{
    GIVEN("A graph") {
        automaton::graph graph;
        WHEN("A state is added to the graph")
        {
            automaton::state* state = graph.new_state();
            THEN("The state is not null")
            {
                REQUIRE(state != nullptr);
            }

            THEN("The graph contains the state")
            {
                bool found = false;
                for (const auto& other : graph.get_states())
                    if (other.get() == state)
                        found = true;
                REQUIRE(found);
            }
        }
    }
}