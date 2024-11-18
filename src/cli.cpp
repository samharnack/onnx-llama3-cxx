#include <iostream>
#include <string>
#include "chat.hpp"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " <command> <model_path>" << std::endl;
        std::cerr << "commands: chat" << std::endl;
        return -1;
    }

    std::string command = argv[1];
    
    if (command == "chat") {
        const char* model = argv[2];
        chat(model);
    } else {
        std::cerr << "unknown command: " << command << std::endl;
        std::cerr << "supported commands: chat" << std::endl;
        return -1;
    }

    return 0;
}