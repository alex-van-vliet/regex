#include "parser.hh"

#include "character.hh"
#include "concatenation.hh"
#include "disjunction.hh"

namespace ast::parser
{
    parser::parser(lexer& lexer): lexer_{lexer}
    {
    }

    node* parser::parse()
    {
        lexer_.eat();
        return parse_disjunction();
    }

    node* parser::parse_disjunction()
    {
        node* expression = parse_concatenation();
        while (lexer_.current() == token::BAR) {
            lexer_.eat();
            expression = new disjunction(expression, parse_concatenation());
        }
        return expression;
    }

    node* parser::parse_concatenation()
    {
        node* expression = parse_expression();
        while (lexer_.current() == token::CHARACTER) {
            expression = new concatenation(expression, parse_expression());
        }
        return expression;
    }

    node* parser::parse_expression()
    {
        node* expression = new character(lexer_.value());
        lexer_.eat();
        return expression;
    }
}
