#include <sstream>
#include "catch.hpp"
#include "parser.hh"
#include "character.hh"

SCENARIO("The parser can build an AST", "[parser]") {
    GIVEN("A parser with a lexer") {
        auto stream = std::stringstream();
        auto lexer = ast::parser::lexer(stream);
        auto parser = ast::parser::parser(lexer);
        WHEN("The next token is a character") {
            stream << "t";
            THEN("The AST contains only a token node") {
                ast::node* node = parser.parse();
                ast::character* ast_token = dynamic_cast<ast::character*>(node);
                THEN("The node contains the character") {
                    REQUIRE(ast_token->value() == 't');
                    delete(node);
                }
            }
        }
    }
}