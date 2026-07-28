#include <cstring>
#include <iostream>

const char* version = "0.1.0";

int main(int argc, char* argv[]) {
    // Arguments loop
    bool verbose_mode = false;
    std::string source_file = "";
    for(int i=1;i<argc;i++) {
        if(i==1&&strcmp(argv[1], "-version")==0) {
            std::cout << "MicroBasic Compiler " << version << "\n";
            return 0;
        }
        else {
            std::string arg(argv[i]);
            if((arg.ends_with(".basic")||arg.ends_with(".bas"))&&source_file.empty()) {
                source_file = arg;
            }
        }
    }
    return 0;
}