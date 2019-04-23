#include "parser.hh"

#include "character.hh"
#include "concatenation.hh"
#include "disjunction.hh"
#include "kleene.hh"
#include "parser_error.hh"

namespace ast::parser
{
    parser::parser(lexer& lexer): lexer_{lexer}
    {
    }

    node* parser::parse()
    {
        lexer_.eat();
        node* expression = parse_disjunction();
        if (lexer_.current() != token::END) {
            throw parser_error("Expected end of stream.");
        }
        return expression;
    }

    node* parser::parse_disjunction()
    {
        node* expression = parse_concatenation();
        if (lexer_.current() == token::BAR) {
            lexer_.eat();
            expression = new disjunction(expression, parse_disjunction());
        }
        return expression;
    }

    node* parser::parse_concatenation()
    {
        node* expression = parse_kleene();
        if (lexer_.current() == token::CHARACTER
            || lexer_.current() == token::OPENING_PARENTHESIS) {
            expression = new concatenation(expression, parse_concatenation());
        }
        return expression;
    }

    node* parser::parse_kleene()
    {
        node* expression = parse_expression();
        if (lexer_.current() == token::STAR) {
            lexer_.eat();
            expression = new kleene(expression);
        }
        if (lexer_.current() == token::STAR) {
            throw parser_error("A star is followed by another star.");
        }
        return expression;
    }

    node* parser::parse_expression()
    {
        if (lexer_.current() == token::OPENING_PARENTHESIS) {
            lexer_.eat();
            node* expression = parse_disjunction();
            if (lexer_.current() != token::CLOSING_PARENTHESIS) {
                throw parser_error("No closing parenthesis found after opening parenthesis.");
            }
            lexer_.eat();
            return expression;
        } else if (lexer_.current() == token::CLOSING_PARENTHESIS) {
            throw parser_error("Unexpected closing parenthesis.");
        } else {
            node* expression = new character(lexer_.value());
            lexer_.eat();
            return expression;
        }
    }
}
