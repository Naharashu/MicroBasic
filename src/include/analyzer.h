#ifndef B_ANALYZER_H
#define B_ANALYZER_H

#include "lexer.h"
inline struct analyzer {
    bool is_error = false;
    void variable_const(const token& t);
    void isfunction(const token& t);
} analyzer;


#endif