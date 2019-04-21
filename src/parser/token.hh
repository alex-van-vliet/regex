#pragma once

namespace parser
{
    enum class token
    {
        BEGIN,
        DOT,
        STAR,
        OPENING_PARENTHESIS,
        CLOSING_PARENTHESIS,
        CHARACTER,
        BACKSLASH,
        ERROR,
        END
    };
}