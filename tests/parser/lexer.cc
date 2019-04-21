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
        WHEN("a dot is the next character in the stream") {
            stream << '.';
            lexer.eat();
            THEN("the token is dot") {
                REQUIRE(lexer.current() == parser::token::DOT);
            }
            THEN("the value is a dot") {
                REQUIRE(lexer.value() == '.');
            }
        }
        WHEN("a star is the next character in the stream") {
            stream << '*';
            lexer.eat();
            THEN("the token is star") {
                REQUIRE(lexer.current() == parser::token::STAR);
            }
            THEN("the value is a star") {
                REQUIRE(lexer.value() == '*');
            }
        }
        WHEN("an opening parenthesis is the next character in the stream") {
            stream << '(';
            lexer.eat();
            THEN("the token is an opening parenthesis") {
                REQUIRE(lexer.current() == parser::token::OPENING_PARENTHESIS);
            }
            THEN("the value is an opening parenthesis") {
                REQUIRE(lexer.value() == '(');
            }
        }
        WHEN("a closing parenthesis is the next character in the stream") {
            stream << ')';
            lexer.eat();
            THEN("the token is a closing parenthesis") {
                REQUIRE(lexer.current() == parser::token::CLOSING_PARENTHESIS);
            }
            THEN("the value is a closing parenthesis") {
                REQUIRE(lexer.value() == ')');
            }
        }
        WHEN("an unknown character is the next character in the stream") {
            stream << 't';
            lexer.eat();
            THEN("the token is a character") {
                REQUIRE(lexer.current() == parser::token::CHARACTER);
            }
            THEN("the value is the character") {
                REQUIRE(lexer.value() == 't');
            }
        }
    }
}