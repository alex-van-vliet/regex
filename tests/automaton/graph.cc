#include <sstream>
#include <catch.hpp>
#include <algorithm>
#include "automaton/graph.hh"
#include "automaton/transition.hh"
#include "automaton/transitions/epsilon.hh"

SCENARIO("The graph can link states with transitions", "[graph]")
{
    GIVEN("A graph with two states and a transition") {
        automaton::graph graph;
        automaton::state* state1 = graph.new_state();
        automaton::state* state2 = graph.new_state();
        automaton::transition* transition1 = graph.new_transition<automaton::transitions::epsilon>(state1, state2);
        graph.set_initial(state1, true);
        graph.set_final(state2, true);

        THEN("state1 is not null")
        {
            REQUIRE(state1 != nullptr);
        }

        THEN("state2 is not null")
        {
            REQUIRE(state2 != nullptr);
        }

        THEN("transition1 is not null")
        {
            REQUIRE(transition1 != nullptr);
        }

        WHEN("The graph is merged into an empty graph")
        {
            automaton::graph other;
            other.merge(graph);

            THEN("state1 is now in other")
            {
                REQUIRE(other.get_states().find(state1) != other.get_states().end());
            }

            THEN("state1 is not in graph")
            {
                REQUIRE(graph.get_states().find(state1) == other.get_states().end());
            }

            THEN("state2 is now in other")
            {
                REQUIRE(other.get_states().find(state2) != other.get_states().end());
            }

            THEN("state2 is not in graph")
            {
                REQUIRE(graph.get_states().find(state2) == other.get_states().end());
            }

            THEN("state1 is initial in other")
            {
                REQUIRE(other.get_initial_states().find(state1) != other.get_initial_states().end());
            }

            THEN("state1 is not initial in graph")
            {
                REQUIRE(graph.get_initial_states().find(state1) == graph.get_initial_states().end());
            }

            THEN("state2 is final in other")
            {
                REQUIRE(other.get_final_states().find(state2) != other.get_final_states().end());
            }

            THEN("state2 is not final in graph")
            {
                REQUIRE(graph.get_final_states().find(state2) == graph.get_final_states().end());
            }

            THEN("transition1 is now in other")
            {
                REQUIRE(other.get_transitions().find(transition1) != other.get_transitions().end());
            }

            THEN("transition1 is not in graph")
            {
                REQUIRE(graph.get_transitions().find(transition1) == graph.get_transitions().end());
            }
        }

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
                REQUIRE(graph.get_transitions().find(transition) != graph.get_transitions().end());
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
                REQUIRE(graph.get_states().find(state) != graph.get_states().end());
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