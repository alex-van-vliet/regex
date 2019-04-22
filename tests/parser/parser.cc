#include <sstream>
#include "catch.hpp"
#include "parser.hh"

SCENARIO("The parser can build an AST", "[parser]") {
    GIVEN("A parser with a lexer") {
        auto stream = std::stringstream();
        auto lexer = parser::lexer(stream);
        auto parser : parser::parser(lexer);
    }
}