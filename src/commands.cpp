#include "include/commands.h"
#include "app/hello.h"
#include "app/Soundplayer.h"

std::map<std::string, void(*)()> command_table;

void InitCommands() {
    command_table["hello"] = hello_main;
    command_table["soundplayer"] = Soundplayer_main;
}
