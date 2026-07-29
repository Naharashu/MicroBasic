#ifndef B_PARSER_H
#define B_PARSER_H

#include "ast.h"
#include "lexer.h"
#include <cstdint>
#include <stdexcept>
#include <vector>
struct parser {
    astptr parse_factor();
    astptr parse_term();
    astptr parse_pow();
    astptr parse_unary();
    astptr parse_expr();
    astptr parse_and_b();
    astptr parse_or_b();
    astptr parse_xor();
    astptr parse_shift();
    astptr parse_cmp();
    astptr parse_equal();
    
    astptr parse_assignment();
    astptr parse_call();
    astptr parse_statement();
    std::vector<astptr> parse();

    std::vector<token> lexed;
    uint64_t indx = 0;

    token peek() {
        if (lexed.size() > indx)
            return lexed[indx];
        else {
            throw std::runtime_error("Unexpected end of input\n");
        }
    }

    inline void consume() {
        indx++;
    }
};

#endif