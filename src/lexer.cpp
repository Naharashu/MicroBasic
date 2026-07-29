#include "include/lexer.h"
#include "include/err.h"
#include <cctype>
#include <cstdint>
#include <cstdlib>



void lexer::lex() {
    for(uint32_t i=0;i<code.size();i++) {
        char c = code[i]; // current char

        if(c=='\t'||c==' '||c=='\r') {
            col++;
            continue;
        }
        if(c=='\n') {
            lexed.emplace_back(token{.type=token_type::NEWLINE, .line=line, .col=col});
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
            case '^': {
                lexed.emplace_back(token{.type=token_type::POWER, .line=line, .col=col});
                col++;
                continue;
            }
            case '`': {
                while(i<code.size()&&code[i]!='\n') col++;
                line++;
                continue;
            }
            case '=': {
                if(i+1<code.size()&&code[i+1]=='=') {
                    lexed.emplace_back(token{.type=token_type::EE, .line=line, .col=col});
                    col++;
                    continue;
                }
                lexed.emplace_back(token{.type=token_type::EQ, .line=line, .col=col});
                col++;
                continue;
            }
            case '<': {
                if(i+1<code.size()&&code[i+1]=='=') {
                    lexed.emplace_back(token{.type=token_type::LE, .line=line, .col=col});
                    col++;
                    continue;
                }
                if(i+1<code.size()&&code[i+1]=='<') {
                    lexed.emplace_back(token{.type=token_type::SHIFTL, .line=line, .col=col});
                    col++;
                    continue;
                }
                lexed.emplace_back(token{.type=token_type::LESS, .line=line, .col=col});
                col++;
                continue;
            }
            case '>': {
                if(i+1<code.size()&&code[i+1]=='=') {
                    lexed.emplace_back(token{.type=token_type::BE, .line=line, .col=col});
                    col++;
                    continue;
                }
                if(i+1<code.size()&&code[i+1]=='>') {
                    lexed.emplace_back(token{.type=token_type::SHIFTR, .line=line, .col=col});
                    col++;
                    continue;
                }
                lexed.emplace_back(token{.type=token_type::BIGGER, .line=line, .col=col});
                col++;
                continue;
            }
            case '!': {
                if(i+1<code.size()&&code[i+1]=='=') {
                    lexed.emplace_back(token{.type=token_type::NE, .line=line, .col=col});
                    col++;
                    continue;
                }
                lexed.emplace_back(token{.type=token_type::NOT, .line=line, .col=col});
                col++;
                continue;
            }
        }

        if(std::isdigit(c)) {
            std::string number;
            bool floating = false;
            while(i<code.size()&&(std::isdigit(code[i])||code[i]=='.')) {
                if(code[i]=='.'&&!floating) floating = true;
                if(code[i]=='.'&&floating) {
                    microbasic_errors_handler.error("Unexpected dot when parsing double", line, col);
                }
                number += code[i];
                col++;
                i++;
            }
            char* endptr;
            double value = std::strtod(number.c_str(), &endptr);
            lexed.emplace_back(token{.val=value, .type=token_type::NUMBER, .line=line, .col=col});
            continue;
        }

        if(std::isalpha(c)||c=='_') {
            std::string id;
            while(i<code.size()&&(std::isalnum(code[i])||code[i]=='_')) {
                id+=code[i];
                col++;
                i++;
            }
            if(id=="LET") lexed.emplace_back(token{.type=token_type::LET, .line=line, .col=col});
            else if(id=="CONST") lexed.emplace_back(token{.type=token_type::CONST, .line=line, .col=col});
            else if(id=="GOTO") lexed.emplace_back(token{.type=token_type::GOTO, .line=line, .col=col});
            else if(id=="GOSUB") lexed.emplace_back(token{.type=token_type::GOSUB, .line=line, .col=col});
            else if(id=="PRINT") lexed.emplace_back(token{.type=token_type::PRINT, .line=line, .col=col});
            else if(id=="INPUT") lexed.emplace_back(token{.type=token_type::INPUT, .line=line, .col=col});
            else if(id=="IF") lexed.emplace_back(token{.type=token_type::IF, .line=line, .col=col});
            else if(id=="THEN") lexed.emplace_back(token{.type=token_type::THEN, .line=line, .col=col});
            else if(id=="ELSE") lexed.emplace_back(token{.type=token_type::ELSE, .line=line, .col=col});
            else if(id=="WHILE") lexed.emplace_back(token{.type=token_type::WHILE, .line=line, .col=col});
            else if(id=="WEND") lexed.emplace_back(token{.type=token_type::WEND, .line=line, .col=col});
            else if(id=="FOR") lexed.emplace_back(token{.type=token_type::FOR, .line=line, .col=col});
            else if(id=="NEXT") lexed.emplace_back(token{.type=token_type::NEXT, .line=line, .col=col});
            else if(id=="STEP") lexed.emplace_back(token{.type=token_type::STEP, .line=line, .col=col});
            else if(id=="TO") lexed.emplace_back(token{.type=token_type::TO, .line=line, .col=col});
            else if(id=="RET") lexed.emplace_back(token{.type=token_type::RET, .line=line, .col=col});
            else if(id=="END") lexed.emplace_back(token{.type=token_type::END, .line=line, .col=col});
            else if(id=="AND") lexed.emplace_back(token{.type=token_type::AND_, .line=line, .col=col});
            else if(id=="OR") lexed.emplace_back(token{.type=token_type::OR_, .line=line, .col=col});
            else if(id=="XOR") lexed.emplace_back(token{.type=token_type::XOR, .line=line, .col=col});
            else lexed.emplace_back(token{.type=token_type::ID, .line=line, .col=col});
            continue;
        }
    }
    lexed.emplace_back(token{.type=token_type::EOF_});
}