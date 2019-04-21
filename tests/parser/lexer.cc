#include <sstream>
#include <token.hh>
#include "catch.hpp"
#include "lexer.hh"

SCENARIO("The lexer can parse tokens", "[lexer]") {
    GIVEN("A lexer with a stream") {
        auto stream = std::stringstream();
        auto lexer = parser::lexer(stream);
        WHEN("no token was eaten") {
            THEN("the token is begin") {
                REQUIRE(lexer.current() == parser::token::BEGIN);
            }
            THEN ("the value is null") {
                REQUIRE(lexer.value() == '\0');
            }
        }
        WHEN("the stream is empty") {
            lexer.eat();
            THEN("the token is end") {
                REQUIRE(lexer.current() == parser::token::END);
            }
            THEN("the value is null") {
                REQUIRE(lexer.value() == '\0');
            }
            WHEN("and we add something to the stream") {
                stream << "test";
                lexer.eat();
                THEN("the token is end") {
                    REQUIRE(lexer.current() == parser::token::END);
                }
            }
        }
    }
}