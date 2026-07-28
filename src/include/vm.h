#ifndef B_VM_H
#define B_VM_H

#include <string>
#include <unordered_map>
struct vm {
    std::unordered_map<std::string, double> variables;
};

#endif