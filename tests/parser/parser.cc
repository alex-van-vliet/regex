#include <sstream>
#include "prettyprinter.hh"
#include "catch.hpp"
#include "parser.hh"
#include "character.hh"
#include "concatenation.hh"
#include "disjunction.hh"
#include "kleene.hh"
#include "wildcard.hh"
#include "parser_error.hh"
#include "lexer_error.hh"

SCENARIO("The parser can build an AST", "[parser]")
{
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
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t");
                    delete node;
                }
            }
        }
        WHEN("the next token is a dot") {
            input << ".";
            THEN("the AST contains only a wildcard node") {
                ast::node* node = parser.parse();
                ast::wildcard* ast_wildcard = dynamic_cast<ast::wildcard*>(node);
                REQUIRE(ast_wildcard != nullptr);
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == ".");
                    delete node;
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
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "te");
                    delete node;
                }
            }
        }
        WHEN("the next tokens are a dot and a character")
        {
            input << "t.";
            THEN("the AST contains a concatenation node, a wildcard node and a character node") {
                ast::node* node = parser.parse();
                ast::concatenation* ast_concatenation = dynamic_cast<ast::concatenation*>(node);
                THEN("the node contains a character node and a wildcard node") {
                    ast::character* ast_left_token = dynamic_cast<ast::character*>(ast_concatenation->left());
                    ast::wildcard* ast_right_token = dynamic_cast<ast::wildcard*>(ast_concatenation->right());
                    REQUIRE(ast_left_token->value() == 't');
                    REQUIRE(ast_right_token != nullptr);
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t.");
                    delete node;
                }
            }
        }
        WHEN("the next tokens are a dot and a character")
        {
            input << ".e";
            THEN("the AST contains a concatenation node, a character node and a wildcard node") {
                ast::node* node = parser.parse();
                ast::concatenation* ast_concatenation = dynamic_cast<ast::concatenation*>(node);
                THEN("the node contains a wildcard node and a character node") {
                    ast::wildcard* ast_left_token = dynamic_cast<ast::wildcard*>(ast_concatenation->left());
                    ast::character* ast_right_token = dynamic_cast<ast::character*>(ast_concatenation->right());
                    REQUIRE(ast_left_token != nullptr);
                    REQUIRE(ast_right_token->value() == 'e');
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == ".e");
                    delete node;
                }
            }
        }
        WHEN("the next three characters are a character, a bar, and another character") {
            input << "t|e";
            THEN("the AST contains a disjunction node and two character nodes") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the node contains two character nodes with the characters") {
                    ast::character* ast_left_token = dynamic_cast<ast::character*>(ast_disjunction->left());
                    ast::character* ast_right_token = dynamic_cast<ast::character*>(ast_disjunction->right());
                    REQUIRE(ast_left_token->value() == 't');
                    REQUIRE(ast_right_token->value() == 'e');
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t|e");
                    delete node;
                }
            }
        }
        WHEN("the next tokens are a dot, a bar and a character")
        {
            input << "t|.";
            THEN("the AST contains a disjunction node, a wildcard node and a character node") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the node contains a character node and a wildcard node") {
                    ast::character* ast_left_token = dynamic_cast<ast::character*>(ast_disjunction->left());
                    ast::wildcard* ast_right_token = dynamic_cast<ast::wildcard*>(ast_disjunction->right());
                    REQUIRE(ast_left_token->value() == 't');
                    REQUIRE(ast_right_token != nullptr);
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t|.");
                    delete node;
                }
            }
        }
        WHEN("the next tokens are a dot, a bar and a character")
        {
            input << ".|e";
            THEN("the AST contains a disjunction node, a character node and a wildcard node") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the node contains a wildcard node and a character node") {
                    ast::wildcard* ast_left_token = dynamic_cast<ast::wildcard*>(ast_disjunction->left());
                    ast::character* ast_right_token = dynamic_cast<ast::character*>(ast_disjunction->right());
                    REQUIRE(ast_left_token != nullptr);
                    REQUIRE(ast_right_token->value() == 'e');
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == ".|e");
                    delete node;
                }
            }
        }
        WHEN("the next two characters are a character and a star") {
            input << "t*";
            THEN("the AST contains a kleene node") {
                ast::node* node = parser.parse();
                ast::kleene* ast_kleene = dynamic_cast<ast::kleene*>(node);
                THEN("the node contains a character node with the character") {
                    ast::character* ast_token = dynamic_cast<ast::character*>(ast_kleene->left());
                    REQUIRE(ast_token->value() == 't');
                    delete node;
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t*");
                    delete node;
                }
            }
        }
        WHEN("the next three characters are an opening parenthesis, a character, and a closing parenthesis") {
            input << "(t)";
            THEN("the AST contains only a token node") {
                ast::node* node = parser.parse();
                ast::character* ast_token = dynamic_cast<ast::character*>(node);
                THEN("the node contains the character") {
                    REQUIRE(ast_token->value() == 't');
                    delete node;
                }
                THEN("the pretty printed AST is the same without the parenthesis") {
                    printer(node);
                    REQUIRE(output.str() == "t");
                    delete node;
                }
            }
        }
        WHEN("the next four characters are an opening parenthesis, two characters, and a closing parenthesis") {
            input << "(te)";
            THEN("the AST contains a concatenation node and two character nodes") {
                ast::node* node = parser.parse();
                ast::concatenation* ast_concatenation = dynamic_cast<ast::concatenation*>(node);
                THEN("the node contains two character nodes with the characters") {
                    ast::character* ast_left_token = dynamic_cast<ast::character*>(ast_concatenation->left());
                    ast::character* ast_right_token = dynamic_cast<ast::character*>(ast_concatenation->right());
                    REQUIRE(ast_left_token->value() == 't');
                    REQUIRE(ast_right_token->value() == 'e');
                    delete node;
                }
                THEN("the pretty printed AST is the same without the parenthesis") {
                    printer(node);
                    REQUIRE(output.str() == "te");
                    delete node;
                }
            }
        }
        WHEN("the next five characters are an opening parenthesis, a character, a bar, another character, "
             "and a closing parenthesis") {
            input << "(t|e)";
            THEN("the AST contains a disjunction node and two character nodes") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the node contains two character nodes with the characters") {
                    ast::character* ast_left_token = dynamic_cast<ast::character*>(ast_disjunction->left());
                    ast::character* ast_right_token = dynamic_cast<ast::character*>(ast_disjunction->right());
                    REQUIRE(ast_left_token->value() == 't');
                    REQUIRE(ast_right_token->value() == 'e');
                    delete node;
                }
                THEN("the pretty printed AST is the same without the parenthesis") {
                    printer(node);
                    REQUIRE(output.str() == "t|e");
                    delete node;
                }
            }
        }
        WHEN("the next characters are three characters") {
            input << "tes";
            THEN("the AST contains two concatenation nodes and three character nodes") {
                ast::node* node = parser.parse();
                ast::concatenation* ast_first_concatenation = dynamic_cast<ast::concatenation*>(node);
                THEN("the node contains a character node with the character and a concatenation node") {
                    ast::character* ast_first_token = dynamic_cast<ast::character*>(ast_first_concatenation->left());
                    ast::concatenation* ast_second_concatenation
                        = dynamic_cast<ast::concatenation*>(ast_first_concatenation->right());
                    REQUIRE(ast_first_token->value() == 't');
                    THEN("the right node contains two character nodes with the characters") {
                        ast::character* ast_second_token
                            = dynamic_cast<ast::character*>(ast_second_concatenation->left());
                        ast::character* ast_third_token
                            = dynamic_cast<ast::character*>(ast_second_concatenation->right());
                        REQUIRE(ast_second_token->value() == 'e');
                        REQUIRE(ast_third_token->value() == 's');
                        delete node;
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "tes");
                    delete node;
                }
            }
        }
        WHEN("the next characters are a character, a bar, another character, a bar, and another character") {
            input << "t|e|s";
            THEN("the AST contains two disjunction nodes and three character nodes") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_first_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the node contains a character node with the character and a disjunction node") {
                    ast::character* ast_first_token = dynamic_cast<ast::character*>(ast_first_disjunction->left());
                    ast::disjunction* ast_second_disjunction
                        = dynamic_cast<ast::disjunction*>(ast_first_disjunction->right());
                    REQUIRE(ast_first_token->value() == 't');
                    THEN("the right node contains two character nodes with the characters") {
                        ast::character* ast_second_token
                            = dynamic_cast<ast::character*>(ast_second_disjunction->left());
                        ast::character* ast_third_token
                            = dynamic_cast<ast::character*>(ast_second_disjunction->right());
                        REQUIRE(ast_second_token->value() == 'e');
                        REQUIRE(ast_third_token->value() == 's');
                        delete node;
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t|e|s");
                    delete node;
                }
            }
        }
        WHEN("the next characters are two characters, a bar, and two other characters") {
            input << "te|st";
            THEN("the AST contains a disjunction node, two concatenation nodes, and four character nodes") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the node contains two concatenation nodes") {
                    ast::concatenation* ast_left_concatenation
                        = dynamic_cast<ast::concatenation*>(ast_disjunction->left());
                    ast::concatenation* ast_right_concatenation
                        = dynamic_cast<ast::concatenation*>(ast_disjunction->right());
                    THEN("the left node contains two character nodes with the characters") {
                        ast::character* ast_first_token = dynamic_cast<ast::character*>(ast_left_concatenation->left());
                        ast::character* ast_second_token = dynamic_cast<ast::character*>(ast_left_concatenation->right());
                        REQUIRE(ast_first_token->value() == 't');
                        REQUIRE(ast_second_token->value() == 'e');
                        delete node;
                    }
                    THEN("the right node contains two character nodes with the characters") {
                        ast::character* ast_third_token = dynamic_cast<ast::character*>(ast_right_concatenation->left());
                        ast::character* ast_fourth_token = dynamic_cast<ast::character*>(ast_right_concatenation->right());
                        REQUIRE(ast_third_token->value() == 's');
                        REQUIRE(ast_fourth_token->value() == 't');
                        delete node;
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "te|st");
                    delete node;
                }
            }
        }
        WHEN("the next characters are a character, an opening parenthesis, a character, a bar, another character, "
             "a closing parenthesis, and another character") {
            input << "t(e|s)t";
            THEN("the AST contains a two concatenation nodes, a disjunction node, and four character nodes") {
                ast::node* node = parser.parse();
                ast::concatenation* ast_left_concatenation = dynamic_cast<ast::concatenation*>(node);
                THEN("the node contains a character node with the character and a concatenation node") {
                    ast::character* ast_first_token
                        = dynamic_cast<ast::character*>(ast_left_concatenation->left());
                    ast::concatenation* ast_right_concatenation
                        = dynamic_cast<ast::concatenation*>(ast_left_concatenation->right());
                    REQUIRE(ast_first_token->value() == 't');
                    THEN("the concatenation node contains a disjunction node and a character node with the character") {
                        ast::disjunction* ast_disjunction
                            = dynamic_cast<ast::disjunction*>(ast_right_concatenation->left());
                        ast::character* ast_fourth_token
                            = dynamic_cast<ast::character*>(ast_right_concatenation->right());
                        REQUIRE(ast_fourth_token->value() == 't');
                        THEN("the disjunction node contains two character nodes with the characters") {
                            ast::character* ast_second_token = dynamic_cast<ast::character*>(ast_disjunction->left());
                            ast::character* ast_third_token = dynamic_cast<ast::character*>(ast_disjunction->right());
                            REQUIRE(ast_second_token->value() == 'e');
                            REQUIRE(ast_third_token->value() == 's');
                            delete node;
                        }
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t(e|s)t");
                    delete node;
                }
            }
        }
        WHEN("the next characters are a character, a bar, another character and a star") {
            input << "t|e*";
            THEN("the AST contains one disjunction node, one character node, one kleene node and one character node") {
                ast::node* node = parser.parse();
                ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(node);
                THEN("the disjunction node contains a character node with the character and a kleene node") {
                    ast::character* ast_first_token = dynamic_cast<ast::character*>(ast_disjunction->left());
                    ast::kleene* ast_kleene = dynamic_cast<ast::kleene*>(ast_disjunction->right());
                    REQUIRE(ast_first_token->value() == 't');
                    THEN("the kleene node contains a character node with the character") {
                        ast::character* ast_second_token = dynamic_cast<ast::character*>(ast_kleene->left());
                        REQUIRE(ast_second_token->value() == 'e');
                        delete node;
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "t|e*");
                    delete node;
                }
            }
        }
        WHEN("the next characters are an opening parenthesis, a character, a bar, another character, "
             "a closing parenthesis and a star") {
            input << "(t|e)*";
            THEN("the AST contains one kleene node, one disjunction node, and two character nodes") {
                ast::node* node = parser.parse();
                ast::kleene* ast_kleene = dynamic_cast<ast::kleene*>(node);
                THEN("the kleene node contains a disjunction node") {
                    ast::disjunction* ast_disjunction = dynamic_cast<ast::disjunction*>(ast_kleene->left());
                    THEN("the disjunction node contains two character nodes with the characters") {
                        ast::character* ast_first_token = dynamic_cast<ast::character*>(ast_disjunction->left());
                        ast::character* ast_second_token = dynamic_cast<ast::character*>(ast_disjunction->right());
                        REQUIRE(ast_first_token->value() == 't');
                        REQUIRE(ast_second_token->value() == 'e');
                        delete node;
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "(t|e)*");
                    delete node;
                }
            }
        }
        WHEN("the next three characters are two characters and a star") {
            input << "te*";
            THEN(
                "the AST contains one concatenation node, one character node, one kleene node and one character node") {
                ast::node* node = parser.parse();
                ast::concatenation* ast_concatenation = dynamic_cast<ast::concatenation*>(node);
                THEN("the concatenation node contains a character node with the character and a kleene node") {
                    ast::character* ast_first_token = dynamic_cast<ast::character*>(ast_concatenation->left());
                    ast::kleene* ast_kleene = dynamic_cast<ast::kleene*>(ast_concatenation->right());
                    REQUIRE(ast_first_token->value() == 't');
                    THEN("the kleene node contains a character node with the character") {
                        ast::character* ast_second_token = dynamic_cast<ast::character*>(ast_kleene->left());
                        REQUIRE(ast_second_token->value() == 'e');
                        delete node;
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "te*");
                    delete node;
                }
            }
        }
        WHEN("the next characters are an opening parenthesis, two characters, a closing parenthesis and a star") {
            input << "(te)*";
            THEN("the AST contains one kleene node, one concatenation node, and two character nodes") {
                ast::node* node = parser.parse();
                ast::kleene* ast_kleene = dynamic_cast<ast::kleene*>(node);
                THEN("the kleene node contains a concatenation node") {
                    ast::concatenation* ast_concatenation = dynamic_cast<ast::concatenation*>(ast_kleene->left());
                    THEN("the concatenation node contains two character nodes with the characters") {
                        ast::character* ast_first_token = dynamic_cast<ast::character*>(ast_concatenation->left());
                        ast::character* ast_second_token = dynamic_cast<ast::character*>(ast_concatenation->right());
                        REQUIRE(ast_first_token->value() == 't');
                        REQUIRE(ast_second_token->value() == 'e');
                        delete node;
                    }
                }
                THEN("the pretty printed AST is the same") {
                    printer(node);
                    REQUIRE(output.str() == "(te)*");
                    delete node;
                }
            }
        }
        WHEN("the two next characters are an opening parenthesis and a closing parenthesis") {
            input << "()";
            THEN("a parser error is thrown") {
                REQUIRE_THROWS_AS(parser.parse(), ast::parser::parser_error);
            }
        }
        WHEN("an opening parenthesis is not closed") {
            input << "(";
            THEN("a parser error is thrown") {
                REQUIRE_THROWS_AS(parser.parse(), ast::parser::parser_error);
            }
        }
        WHEN("the next character is a closing parenthesis but no parenthesis was opened") {
            input << ")";
            THEN("a parser error is thrown") {
                REQUIRE_THROWS_AS(parser.parse(), ast::parser::parser_error);
            }
        }
        WHEN("the three next characters are a character and two stars") {
            input << "t**";
            THEN("a parser error is thrown") {
                REQUIRE_THROWS_AS(parser.parse(), ast::parser::parser_error);
            }
        }
        WHEN("the next character is a backslash without a character after") {
            input << "\\";
            THEN("a lexer error is thrown") {
                REQUIRE_THROWS_AS(parser.parse(), ast::parser::lexer_error);
            }
        }
        WHEN("the next two characters are a backslash with a regular character after") {
            input << "\\t";
            THEN("a lexer error is thrown") {
                REQUIRE_THROWS_AS(parser.parse(), ast::parser::lexer_error);
            }
        }
    }
}