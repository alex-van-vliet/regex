add_library(parser
    lexer.cc
    lexer.hh
    token.hh
    parser.cc
    parser.hh
    ast/node.hh
    ast/character.cc
    ast/character.hh
    ast/forward.hh
    visitor/visitor.hh)
target_include_directories(parser PUBLIC . ast visitor)