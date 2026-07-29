
#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

uint8_t registers_allocated = 0;

struct symbol {
    std::string name;
    bool is_const;
    double val;
    std::string strval;
    uint8_t reg;
};

std::array<symbol, 256> table; // MicroBasic supports 256 variables(compared to 26 in TinyBasic)

inline void insert(const symbol& s) {
    table[registers_allocated++] = s;
}

// return false if not found
inline bool exist(const std::string& name) {
    for(int i=registers_allocated-1;i>0;i--) if(table.at(i).name==name) return true;
    return false;
}

inline symbol* search(const std::string& name) {
    for(int i=registers_allocated-1;i>0;i--) {
        if(table.at(i).name==name) {
            return &table.at(i);
        }
    }
    return nullptr;
}