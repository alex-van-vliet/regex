#include <sstream>
#include <catch.hpp>
#include <algorithm>
#include "automaton/graph.hh"
#include "automaton/transition.hh"
#include "automaton/transitions/epsilon.hh"

SCENARIO("The graph can link states with transitions", "[graph]")
{
    GIVEN("A graph with two states") {
        automaton::graph graph;
        automaton::state* state1 = graph.new_state();
        automaton::state* state2 = graph.new_state();

        WHEN("An epsilon transition from state1 to state2 is added to the graph")
        {
            automaton::transition* transition = graph.new_transition<automaton::transitions::epsilon>(state1, state2);

            THEN("The transition is an epsilon transition")
            {
                automaton::transitions::epsilon* epsilon = dynamic_cast<automaton::transitions::epsilon*>(transition);
                REQUIRE(epsilon != nullptr);
            }

            THEN("The source of the transition is state1")
            {
                REQUIRE(transition->get_source() == state1);
            }

            THEN("The destination of the transition is state2")
            {
                REQUIRE(transition->get_destination() == state2);
            }

            THEN("The transition is in the out set of state1")
            {
                REQUIRE(std::find(state1->get_out_transitions().begin(),
                    state1->get_out_transitions().end(), transition) != state1->get_out_transitions().end());
            }

            THEN("The transition is in the in set of state2")
            {
                REQUIRE(std::find(state2->get_in_transitions().begin(),
                    state2->get_in_transitions().end(), transition) != state2->get_in_transitions().end());
            }

            THEN("The graph contains the transition")
            {
                bool found = false;
                for (const auto& other : graph.get_transitions())
                    if (other.get() == transition)
                        found = true;
                REQUIRE(found);
            }
        }

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