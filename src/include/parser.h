#ifndef B_PARSER_H
#define B_PARSER_H

#include "ast.h"
#include "lexer.h"
#include <cstdint>
#include "errors.h"
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

    inline void consume_token(const token_type& expected) {
        if(lexed[indx].type!=expected) {
            if(expected==token_type::ID) microbasic_errors_handler.error("Expected identifier", lexed[indx].line, lexed[indx].col);
            else microbasic_errors_handler.error("Unexpected token", lexed[indx].line, lexed[indx].col);
            return;
        } else {
            if(indx<lexed.size()) indx++;
        }
    }

    inline void sync() {
        while(indx<lexed.size()) {
            if(lexed[indx++].type==token_type::NEWLINE) return;
            else indx++;
        }
    }
};

#endif