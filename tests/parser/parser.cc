#include <sstream>
#include <visitor/prettyprinter.hh>
#include "catch.hpp"
#include "parser.hh"
#include "character.hh"
#include "concatenation.hh"
#include "disjunction.hh"

SCENARIO("The parser can build an AST", "[parser]") {
    GIVEN("A parser with its a lexer and a pretty printer") {
        auto input = std::stringstream();
        auto output = std::stringstream();
        auto lexer = ast::parser::lexer(input);
        auto parser = ast::parser::parser(lexer);
        auto printer = ast::visitor::prettyprinter(output);
        WHEN("the next token is a character") {
            input << "t";
            THEN("the AST contains only a token node") {
                ast::node* node = parser.parse();
                ast::character* ast_token = dynamic_cast<ast::character*>(node);
                THEN("the node contains the character") {
                    REQUIRE(ast_token->value() == 't');
                    delete(node);
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t");
                    delete(node);
                }
            }
        }
        WHEN("the next two tokens are characters") {
            input << "te";
            THEN("the AST contains a concatenation node and two character nodes") {
                ast::node* node = parser.parse();
                ast::concatenation* ast_concatenation = dynamic_cast<ast::concatenation*>(node);
                THEN("the node contains two character nodes with the characters") {
                    ast::character* ast_left_token = dynamic_cast<ast::character*>(ast_concatenation->left());
                    ast::character* ast_right_token = dynamic_cast<ast::character*>(ast_concatenation->right());
                    REQUIRE(ast_left_token->value() == 't');
                    REQUIRE(ast_right_token->value() == 'e');
                    delete(node);
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "te");
                    delete(node);
                }
            }
        }
        WHEN("the next three characters are a character, a bar, and another character") {
            input << "t|e";
            THEN("the AST contains an dijunction node and two character nodes") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the node contains two character nodes with the characters") {
                    ast::character* ast_left_token = dynamic_cast<ast::character*>(ast_disjunction->left());
                    ast::character* ast_right_token = dynamic_cast<ast::character*>(ast_disjunction->right());
                    REQUIRE(ast_left_token->value() == 't');
                    REQUIRE(ast_right_token->value() == 'e');
                    delete(node);
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t|e");
                    delete(node);
                }
            }
        }
    }
}