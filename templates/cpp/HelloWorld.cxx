#include <iostream>
#include <vector>
#include <string>

// using header-only logger from https://github.com/gabime/spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

auto logger = spdlog::stdout_color_mt("console");

/*
    Basic template for simple C++ project with easy example for parsing of CL arguments and a header-only logger
    Author: Carsten Bittrich 2020
*/

int ShortFuncTest( int i) {
    return i*i;
}

int main (int argc, char **argv) {
    // check if -d or --debug are requested
    bool logDebug = false;

    for (int i = 1; i < argc; i++) {
        std::string this_arg = argv[i];
        if (this_arg == "-d" || this_arg == "--debug") {
            logDebug = true;
        }
    }
    // Set global log level to debug
    if (logDebug) {
        spdlog::set_level(spdlog::level::debug);
    }
    logger->debug("Switching to debug log level");

    std::cout << " Hello World!" << std::endl;
    return 0;
}

