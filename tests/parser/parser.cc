#include <sstream>
#include "catch.hpp"
#include "parser.hh"

SCENARIO("The parser can build an AST", "[parser]") {
    GIVEN("A parser with a lexer") {
        auto stream = std::stringstream();
        auto lexer = parser::lexer(stream);
        auto parser = parser::parser(lexer);
        WHEN("The next token is a character") {
            stream << "t";
            THEN("The AST contains only a token node") {
                parser::ast::node* node = parser.parse();
                parser::ast::character* ast_token = dynamic_cast<parser::ast::character*>(node);
                THEN("The node contains the character") {
                    REQUIRE(ast_token.value() == 't');
                }
            }
        }
    }
}