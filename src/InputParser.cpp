
#include "InputParser.h"
#include <cstddef>
#include <iostream>

InputParser::InputParser(void) {}

InputParser::~InputParser(void) {}

void InputParser::read_args(int ac, const char **av) {

    std::string key, value;

    for (int i = 1; i < ac; i++) {
        key = av[i];
        if (key.substr(0, 2) != "--") {
            ; //error
        }
        if (option_bool.find(key.substr(2)) != option_bool.end()) {
            set_option(key.substr(2), 1);
        } else if (option_str.find(key.substr(2)) != option_str.end()) {
            value = av[++i];
            set_option(key.substr(2), value);
        } else {
            ; // error
        }
    }
}

void InputParser::register_option(OptionType_t type, const std::string option) {

    if (type == BOOL)
        option_bool.insert(std::pair<std::string, bool>(option, false));
    else
        option_str.insert(std::pair<std::string, std::string>(option, ""));
}

void InputParser::register_option(OptionType_t type, const std::string option[], size_t size) {

    for (size_t i = 0; i < size; i++) {
        register_option(type, option[i]);
    }
}

void InputParser::set_option(std::string key, bool value) {

    auto elem = option_bool.find(key);

    if (elem != option_bool.end()) {
        (*elem).second = value;
        return ;
    }
//    std::errc << "illegal option: -- " << key << std::endl;
//    usage();
}

void InputParser::set_option(std::string key, std::string value) {

    auto elem = option_str.find(key);

    if (elem != option_str.end()) {
        (*elem).second = value;
        return ;
    }
//    std::errc << "illegal option: -- " << key << std::endl;
//    usage();
}

std::map<std::string, bool> InputParser::get_list_bool(void) const {

    return option_bool;
}

std::map<std::string, std::string> InputParser::get_list_str(void) const {

    return option_str;
}

std::ostream &operator<<(std::ostream &out, const InputParser &inst) {

    std::map<std::string, bool> map_bool = inst.get_list_bool();
    std::map<std::string, std::string> map_str = inst.get_list_str();

    for (auto it = map_bool.begin(); it != map_bool.end(); it++) {
        out << it->first << " -> " << it->second << std::endl;
    }

    for (auto it = map_str.begin(); it != map_str.end(); it++) {
        out << it->first << " -> \"" << it->second << "\"" << std::endl;
    }

    return out;
}
