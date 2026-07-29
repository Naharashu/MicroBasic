#include "include/analyzer.h"
#include "include/table.h"
#include "include/err.h"

void analyzer::variable_const(const token& t) {
    if(exist(t.id)) {
        symbol* s = search(t.id);
        if(s->is_const) {
            microbasic_errors_handler.error("Variable is constant", t.line, t.col);
        }
    }
}