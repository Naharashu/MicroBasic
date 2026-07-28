#ifndef B_PREPROCESSOR_H
#define B_PREPROCESSOR_H

#include <fstream>
#include <stdexcept>
#include <string>

struct preprocessor {
    std::string compile(const std::string &filename) {
        std::ifstream f(filename);
        std::string res;
        std::string line;
        if (!f.is_open()) {
            throw std::runtime_error("Error: file " + filename + " doesnt exist.");
        }
        auto trim = [](std::string &s) {
            size_t start = s.find_first_not_of(" \"\t\r\n");
            size_t end = s.find_last_not_of(" \"\t\r\n");

            if (start == std::string::npos) {
                s.clear();
                return;
            }

            s = s.substr(start, end - start + 1);
        };
        while (std::getline(f, line)) {
            if(line.rfind("#include", 0)==0) {
                std::string include = line.substr(8);
                trim(include);

                res += compile(include);
            } else {
                res += line;
            }
        }
    }
};

#endif