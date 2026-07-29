#ifndef B_LEXER_H
#define B_LEXER_H

#include <cstdint>
#include <string>
#include <vector>

enum class token_type : uint8_t {
    NUMBER,
    ID,
    EQ,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    XOR,
    AND_,
    OR_,
    SHIFTL,
    SHIFTR,
    POWER,
    EE,
    LESS,
    BIGGER,
    BE,
    LE,
    NE,
    NOT,
    APOSTROPHE,
    L_BRACKET,
    R_BRACKET,
    LET,
    CONST,
    GOTO,
    GOSUB,
    PRINT,
    INPUT,
    IF,
    THEN,
    ELSE,
    WHILE,
    WEND,
    FOR,
    TO,
    NEXT,
    STEP,
    END,
    RET,
    NEWLINE,
    EOF_
};

struct token {
    double val=0;
    enum token_type type;
    std::string id="";
    uint32_t line=1;
    uint16_t col=1;
};

struct lexer {
    std::vector<token> lexed;
    std::string filename;
    std::string code;
    uint32_t line=1;
    uint16_t col=1;

    lexer(const std::string& fname, const std::string& src) : filename(fname), code(src) {}
    void lex();
};

#endif