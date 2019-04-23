#pragma once

namespace ast::parser
{
    enum class token
    {
        BEGIN,
        DOT,
        BAR,
        STAR,
        OPENING_PARENTHESIS,
        CLOSING_PARENTHESIS,
        CHARACTER,
        BACKSLASH,
        ERROR,
        END
    };
}