add_library(parser
    lexer.cc
    lexer.hh
    token.hh)
target_include_directories(parser PUBLIC .)