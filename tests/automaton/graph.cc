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

            THEN("The state is not in the initial set")
            {
                REQUIRE(graph.get_initial_states().find(state) == graph.get_initial_states().end());
            }

            THEN("The state is not in the final set")
            {
                REQUIRE(graph.get_final_states().find(state) == graph.get_final_states().end());
            }

            WHEN("The state is set as initial")
            {
                graph.set_initial(state, true);

                THEN("The state is in the initial set")
                {
                    REQUIRE(graph.get_initial_states().find(state) != graph.get_initial_states().end());


                    WHEN("The state is set as initial")
                    {
                        graph.set_initial(state, true);

                        THEN("The state is in the initial set")
                        {
                            REQUIRE(graph.get_initial_states().find(state) != graph.get_initial_states().end());
                        }
                    }

                    WHEN("The state is set as non initial")
                    {
                        graph.set_initial(state, false);

                        THEN("The state is not in the initial set")
                        {
                            REQUIRE(graph.get_initial_states().find(state) == graph.get_initial_states().end());
                        }
                    }
                }
            }

            WHEN("The state is set as non initial")
            {
                graph.set_initial(state, false);

                THEN("The state is not in the initial set")
                {
                    REQUIRE(graph.get_initial_states().find(state) == graph.get_initial_states().end());
                }
            }

            THEN("The state is not in the initial set")
            {
                REQUIRE(graph.get_initial_states().find(state) == graph.get_initial_states().end());
            }

            WHEN("The state is set as initial")
            {
                graph.set_initial(state, true);

                THEN("The state is in the initial set")
                {
                    REQUIRE(graph.get_initial_states().find(state) != graph.get_initial_states().end());


                    WHEN("The state is set as initial")
                    {
                        graph.set_initial(state, true);

                        THEN("The state is in the initial set")
                        {
                            REQUIRE(graph.get_initial_states().find(state) != graph.get_initial_states().end());
                        }
                    }

                    WHEN("The state is set as non initial")
                    {
                        graph.set_initial(state, false);

                        THEN("The state is not in the initial set")
                        {
                            REQUIRE(graph.get_initial_states().find(state) == graph.get_initial_states().end());
                        }
                    }
                }
            }

            WHEN("The state is set as non initial")
            {
                graph.set_initial(state, false);

                THEN("The state is not in the initial set")
                {
                    REQUIRE(graph.get_initial_states().find(state) == graph.get_initial_states().end());
                }
            }

            WHEN("The state is set as final")
            {
                graph.set_final(state, true);

                THEN("The state is in the final set")
                {
                    REQUIRE(graph.get_final_states().find(state) != graph.get_final_states().end());


                    WHEN("The state is set as final")
                    {
                        graph.set_final(state, true);

                        THEN("The state is in the final set")
                        {
                            REQUIRE(graph.get_final_states().find(state) != graph.get_final_states().end());
                        }
                    }

                    WHEN("The state is set as non final")
                    {
                        graph.set_final(state, false);

                        THEN("The state is not in the final set")
                        {
                            REQUIRE(graph.get_final_states().find(state) == graph.get_final_states().end());
                        }
                    }
                }
            }

            WHEN("The state is set as non final")
            {
                graph.set_final(state, false);

                THEN("The state is not in the final set")
                {
                    REQUIRE(graph.get_final_states().find(state) == graph.get_final_states().end());
                }
            }
        }
    }
}