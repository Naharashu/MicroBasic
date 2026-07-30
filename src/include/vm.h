#ifndef B_VM_H
#define B_VM_H

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>

enum bytecode : uint8_t {
    LOAD_TEMP,
    LOAD_VAR,
    ADD,
    SUB,
    MUL,
    DIV,
    SHIFTL,
    SHIFTR,
    XOR,
    AND_,
    OR_,
    POW,
    PRINT,
    INPUT,
    JMP_FALSE,
    JMP,
    JMP_TRUE,
    INC,
    DEC,
    CALL,
    RET,
    CMP,
    HLT
};

using registers = struct {
    double value;
    std::string str;
};

inline struct vm {
    std::array<registers, 256> regs;
    std::array<registers, 32> temp;

    std::array<uint64_t, 1024> callstack;
    uint16_t csp;
} vm;

#endif