#include "include/lexer.h"
#include <cstdint>



void lexer::lex() {
    for(uint32_t i=0;i<code.size();i++) {
        char c = code[i]; // current char

        if(c=='\t'||c==' '||c=='\r') {
            col++;
            continue;
        }
        if(c=='\n') {
            line++;
            continue;
        }

        switch(c) {
            case '+': {
                lexed.emplace_back(token{.type=token_type::PLUS, .line=line, .col=col});
                col++;
                continue;
            }
            case '-': {
                lexed.emplace_back(token{.type=token_type::MINUS, .line=line, .col=col});
                col++;
                continue;
            }
            case '*': {
                lexed.emplace_back(token{.type=token_type::STAR, .line=line, .col=col});
                col++;
                continue;
            }
            case '/': {
                lexed.emplace_back(token{.type=token_type::SLASH, .line=line, .col=col});
                col++;
                continue;
            }
            case '`': {
                while(i<code.size()&&code[i]!='\n') col++;
                line++;
                continue;
            }
            case '\n': {
                line++;
                continue;
            }
        }
    }
}