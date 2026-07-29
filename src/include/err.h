#ifndef B_ERR_H
#define B_ERR_H

#include <cstdint>
#include <string>
#include <iostream>

enum class microbasic_errors : uint8_t {
    NOERR = 0,
    UNKNOWN_ERROR,
    UNEXPECTED_TOKEN,
};

struct microbasic_errors_handler {
    enum microbasic_errors err;
    std::string main_error = "";
    std::string filename;
    uint8_t err_count = 0;
    std::string describe() {
        switch(err) {
            case microbasic_errors::NOERR: {
                return "Successful";
            }
            case microbasic_errors::UNKNOWN_ERROR: {
                return "Unknown error: ";
            }
            case microbasic_errors::UNEXPECTED_TOKEN: {
                return "Unexpected token: ";
            }
        }
    }

    void error(const std::string& errmsg, uint32_t line, uint16_t col) {
        std::cerr << filename << ':'
        << line << ':'
        << col << ':'
        << "\e[0;91m error: " << errmsg
        << '\e[0m' << '\n';
        err_count++;
    }
} microbasic_errors_handler;

#endif