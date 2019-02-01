
#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <string>
#include <map>

class InputParser {

public:

    typedef enum OptionType {
        BOOL,
        STRING
    }            OptionType_t;

	InputParser(void);
	~InputParser(void);

    void read_args(int ac, const char **av);
    void register_option(OptionType_t type, const std::string option);
    void register_option(OptionType_t type, const std::string option[], size_t size);

    std::map<std::string, bool>        get_list_bool(void) const;
    std::map<std::string, std::string> get_list_str(void) const;

private:

    void set_option(std::string key, bool value);
    void set_option(std::string key, std::string value);

    std::map<std::string, bool>        option_bool;
    std::map<std::string, std::string> option_str;

};

std::ostream &operator<<(std::ostream &out, const InputParser &inst);

#endif
