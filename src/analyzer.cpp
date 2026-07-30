#include "include/analyzer.h"
#include "include/table.h"
#include "include/errors.h"

void analyzer::variable_const(const token& t) {
    is_error = false;
    if(exist(t.id)) {
        symbol* s = search(t.id);
        if(s->is_const) {
            is_error = true;
            microbasic_errors_handler.error("Variable is constant", t.line, t.col);
        }
    }
}

void analyzer::isfunction(const token& t) {
    is_error = false;
    for(uint32_t i = 0;i<builtin_funcs.size();i++) if(builtin_funcs[i]==t.id) return;
    is_error = true;
    microbasic_errors_handler.error("Variable is function", t.line, t.col);
}