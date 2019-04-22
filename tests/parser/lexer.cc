#include <sstream>
#include <catch.hpp>
#include "lexer.hh"

SCENARIO("The lexer can parse tokens", "[lexer]") {
    GIVEN("A lexer with a stream") {
        auto stream = std::stringstream();
        auto lexer = ast::parser::lexer(stream);
        WHEN("no token was eaten") {
            THEN("the token is begin") {
                REQUIRE(lexer.current() == ast::parser::token::BEGIN);
            }
            THEN ("the value is null") {
                REQUIRE(lexer.value() == '\0');
            }
        }
        WHEN("the stream is empty") {
            lexer.eat();
            THEN("the token is end") {
                REQUIRE(lexer.current() == ast::parser::token::END);
            }
            THEN("the value is null") {
                REQUIRE(lexer.value() == '\0');
            }
            WHEN("and we add something to the stream") {
                stream << "test";
                lexer.eat();
                THEN("the token is end") {
                    REQUIRE(lexer.current() == ast::parser::token::END);
                }
            }
        }
        WHEN("a dot is the next character in the stream") {
            stream << '.';
            lexer.eat();
            THEN("the token is dot") {
                REQUIRE(lexer.current() == ast::parser::token::DOT);
            }
            THEN("the value is a dot") {
                REQUIRE(lexer.value() == '.');
            }
        }
        WHEN("a star is the next character in the stream") {
            stream << '*';
            lexer.eat();
            THEN("the token is star") {
                REQUIRE(lexer.current() == ast::parser::token::STAR);
            }
            THEN("the value is a star") {
                REQUIRE(lexer.value() == '*');
            }
        }
        WHEN("an opening parenthesis is the next character in the stream") {
            stream << '(';
            lexer.eat();
            THEN("the token is opening parenthesis") {
                REQUIRE(lexer.current() == ast::parser::token::OPENING_PARENTHESIS);
            }
            THEN("the value is an opening parenthesis") {
                REQUIRE(lexer.value() == '(');
            }
        }
        WHEN("a closing parenthesis is the next character in the stream") {
            stream << ')';
            lexer.eat();
            THEN("the token is closing parenthesis") {
                REQUIRE(lexer.current() == ast::parser::token::CLOSING_PARENTHESIS);
            }
            THEN("the value is a closing parenthesis") {
                REQUIRE(lexer.value() == ')');
            }
        }
        WHEN("an regular character is the next character in the stream") {
            stream << 't';
            lexer.eat();
            THEN("the token is character") {
                REQUIRE(lexer.current() == ast::parser::token::CHARACTER);
            }
            THEN("the value is the character") {
                REQUIRE(lexer.value() == 't');
            }
        }
        WHEN("a backslash is the next character in the stream") {
            stream << '\\';
            WHEN("the backslash is followed by a dot") {
                stream << '.';
                lexer.eat();
                THEN("the token is character") {
                    REQUIRE(lexer.current() == ast::parser::token::CHARACTER);
                }
                THEN("the value is a dot") {
                    REQUIRE(lexer.value() == '.');
                }
            }
            WHEN("the backslash is followed by a star") {
                stream << '*';
                lexer.eat();
                THEN("the token is character") {
                    REQUIRE(lexer.current() == ast::parser::token::CHARACTER);
                }
                THEN("the value is a star") {
                    REQUIRE(lexer.value() == '*');
                }
            }
            WHEN("the backslash is followed by an opening parenthesis") {
                stream << '(';
                lexer.eat();
                THEN("the token is character") {
                    REQUIRE(lexer.current() == ast::parser::token::CHARACTER);
                }
                THEN("the value is an opening parenthesis") {
                    REQUIRE(lexer.value() == '(');
                }
            }
            WHEN("the backslash is followed by a closing parenthesis") {
                stream << ')';
                lexer.eat();
                THEN("the token is character") {
                    REQUIRE(lexer.current() == ast::parser::token::CHARACTER);
                }
                THEN("the value is a closing parenthesis") {
                    REQUIRE(lexer.value() == ')');
                }
            }
            WHEN("the backslash is followed by a backslash") {
                stream << '\\';
                lexer.eat();
                THEN("the token is character") {
                    REQUIRE(lexer.current() == ast::parser::token::CHARACTER);
                }
                THEN("the value is a backslash") {
                    REQUIRE(lexer.value() == '\\');
                }
            }
            WHEN("the backslash is followed by a regular character") {
                stream << 't';
                lexer.eat();
                THEN("the token is error") {
                    REQUIRE(lexer.current() == ast::parser::token::ERROR);
                }
                THEN("the value is null") {
                    REQUIRE(lexer.value() == '\0');
                }
            }
            WHEN("the backslash is the last character") {
                lexer.eat();
                THEN("the token is error") {
                    REQUIRE(lexer.current() == ast::parser::token::ERROR);
                }
                THEN("the value is null") {
                    REQUIRE(lexer.value() == '\0');
                }
            }
        }
    }
}