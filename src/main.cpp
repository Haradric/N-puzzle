
#include "InputParser.h"
#include <iostream>

int main(int ac, const char **av) {

    std::string opt_str[] = {"input", "output"};
	InputParser config;

    config.register_option(InputParser::STRING ,opt_str, sizeof(opt_str)/sizeof(*opt_str));
    config.read_args(ac, av);

    std::cout << config << std::endl;

	return (0);
}
