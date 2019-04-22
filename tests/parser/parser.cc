#include <sstream>
#include <visitor/prettyprinter.hh>
#include "catch.hpp"
#include "parser.hh"
#include "character.hh"

SCENARIO("The parser can build an AST", "[parser]") {
    GIVEN("A parser with its a lexer and a pretty printer") {
        auto input = std::stringstream();
        auto output = std::stringstream();
        auto lexer = ast::parser::lexer(input);
        auto parser = ast::parser::parser(lexer);
        auto printer = ast::visitor::prettyprinter(output);
        WHEN("The next token is a character") {
            input << "t";
            THEN("The AST contains only a token node") {
                ast::node* node = parser.parse();
                ast::character* ast_token = dynamic_cast<ast::character*>(node);
                THEN("The node contains the character") {
                    REQUIRE(ast_token->value() == 't');
                    delete(node);
                }
                THEN("The pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t");
                    delete(node);
                }
            }
        }
    }
}