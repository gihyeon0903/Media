#include <iostream>
#include <string>
#include <map>
#include <thread>
#include "include/commands.h"

int main() {
    InitCommands();

    std::string command;
    std::cout << "Enter command (soundplayer): " << std::endl;

    while (true) {
        std::cout << "> ";
        if (!(std::cin >> command)) {
            std::cout << "\nError reading input or EOF." << std::endl;
            std::cin.clear(); // Clear error state
            break; 
        }

        if (command == "exit") {
            break;
        } 

        auto it = command_table.find(command);
        if (it != command_table.end()) {
            std::thread t(it->second);
            t.detach(); 
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    std::cout << "Press Enter to close window..." << std::endl;
    std::cin.ignore(10000, '\n'); 
    std::cin.get();
    
    return 0;
}
