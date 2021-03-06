#include "lexer.hh"
#include "lexer_error.hh"

namespace ast::parser
{
    lexer::lexer(std::istream& input):
        input_{input},
        current_token_{token::BEGIN},
        current_value_{'\0'}
    {}

    token lexer::current()
    {
        return current_token_;
    }

    char lexer::value()
    {
        return current_value_;
    }

    void lexer::eat()
    {
        if (current_token_ == token::END) {
            return;
        }
        eat_character();
        if (current_token_ == token::BACKSLASH) {
            eat_escaped();
        }
    }

    void lexer::eat_escaped()
    {
        eat_character();
        if (current_token_ == token::END) {
            throw lexer_error("A character is required after a \\.");
        } else if (current_token_ == token::CHARACTER) {
            throw lexer_error("A special character is required after a \\.");
        } else {
            current_token_ = token::CHARACTER;
        }
    }

    void lexer::eat_character()
    {
        if (!(input_ >> current_value_)) {
            current_value_ = '\0';
            current_token_ = token::END;
        } else if (current_value_ == '.') {
            current_token_ = token::DOT;
        } else if (current_value_ == '|') {
            current_token_ = token::BAR;
        } else if (current_value_ == '*') {
            current_token_ = token::STAR;
        } else if (current_value_ == '(') {
            current_token_ = token::OPENING_PARENTHESIS;
        } else if (current_value_ == ')') {
            current_token_ = token::CLOSING_PARENTHESIS;
        } else if (current_value_ == '\\') {
            current_token_ = token::BACKSLASH;
        } else {
            current_token_ = token::CHARACTER;
        }
    }
}