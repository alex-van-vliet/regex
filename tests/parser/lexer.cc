#include <sstream>
#include <token.hh>
#include "catch.hpp"
#include "lexer.hh"

SCENARIO("The lexer can parse tokens", "[lexer]") {
    GIVEN("A lexer with a stream") {
        auto stream = std::stringstream();
        auto lexer = parser::lexer(stream);
    }
}