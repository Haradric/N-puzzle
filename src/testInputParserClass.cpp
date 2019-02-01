
#include "gtest/gtest.h"
#include "InputParser.h"

TEST(InputParserClass, RegisterSimpleParam) {

    const std::string keys[] = {"key1", "key2", "key3"};
    InputParser conf;

    conf.register_option(InputParser::BOOL, keys, sizeof(keys)/sizeof(*keys));
    conf.register_option(InputParser::BOOL, "key4");
    conf.register_option(InputParser::BOOL, std::string("key5"));

    std::map<std::string, bool> ref;
    ref.insert(std::pair<std::string, bool>("key1", 0));
    ref.insert(std::pair<std::string, bool>("key2", 0));
    ref.insert(std::pair<std::string, bool>("key3", 0));
    ref.insert(std::pair<std::string, bool>("key4", 0));
    ref.insert(std::pair<std::string, bool>("key5", 0));

    EXPECT_EQ(ref, conf.get_list_bool());
}

TEST(InputParserClass, RegisterArgParam) {

    const std::string keys[] = {"key1", "key2", "key3"};
    InputParser conf;

    conf.register_option(InputParser::STRING, keys, sizeof(keys)/sizeof(*keys));
    conf.register_option(InputParser::STRING, "key4");
    conf.register_option(InputParser::STRING, std::string("key5"));

    std::map<std::string, std::string> ref;
    ref.insert(std::pair<std::string, std::string>("key1", ""));
    ref.insert(std::pair<std::string, std::string>("key2", ""));
    ref.insert(std::pair<std::string, std::string>("key3", ""));
    ref.insert(std::pair<std::string, std::string>("key4", ""));
    ref.insert(std::pair<std::string, std::string>("key5", ""));

    EXPECT_EQ(ref, conf.get_list_str());
}

TEST(InputParserClass, SetSimpleParam) {

    const char *argv[] = {"argv[0]", "--key1", "--key3", "--key5"};
    const std::string keys[] = {"key1", "key2", "key3", "key4", "key5"};
    InputParser conf;

    conf.register_option(InputParser::BOOL, keys, sizeof(keys)/sizeof(*keys));
    conf.read_args(sizeof(argv)/sizeof(*argv), argv);

    std::map<std::string, bool> ref;
    ref.insert(std::pair<std::string, bool>("key1", 1));
    ref.insert(std::pair<std::string, bool>("key2", 0));
    ref.insert(std::pair<std::string, bool>("key3", 1));
    ref.insert(std::pair<std::string, bool>("key4", 0));
    ref.insert(std::pair<std::string, bool>("key5", 1));

    EXPECT_EQ(ref, conf.get_list_bool());
}

TEST(InputParserClass, SetArgParam) {

    const char *argv[] = {"argv[0]", "--key1", "value1", "--key3", "value3", "--key5", "value5"};
    const std::string keys[] = {"key1", "key2", "key3", "key4", "key5"};
    InputParser conf;

    conf.register_option(InputParser::STRING, keys, sizeof(keys)/sizeof(*keys));
    conf.read_args(sizeof(argv)/sizeof(*argv), argv);

    std::map<std::string, std::string> ref;
    ref.insert(std::pair<std::string, std::string>("key1", "value1"));
    ref.insert(std::pair<std::string, std::string>("key2", ""));
    ref.insert(std::pair<std::string, std::string>("key3", "value3"));
    ref.insert(std::pair<std::string, std::string>("key4", ""));
    ref.insert(std::pair<std::string, std::string>("key5", "value5"));

    EXPECT_EQ(ref, conf.get_list_str());
}

TEST(InputParserClass, OutputOperator) {

    const char *argv[] = {"argv[0]", "--key1", "--key2", "value2", "--key4", "value4", "--key5"};
    const std::string keys1[] = {"key1", "key3", "key5"};
    const std::string keys2[] = {"key2", "key4", "key6"};
    std::stringstream o1, o2;
    InputParser conf;

    conf.register_option(InputParser::BOOL, keys1, sizeof(keys1)/sizeof(*keys1));
    conf.register_option(InputParser::STRING, keys2, sizeof(keys2)/sizeof(*keys2));
    conf.read_args(sizeof(argv)/sizeof(*argv), argv);

    o1 << "key1 -> 1" << std::endl;
    o1 << "key3 -> 0" << std::endl;
    o1 << "key5 -> 1" << std::endl;
    o1 << "key2 -> \"value2\"" << std::endl;
    o1 << "key4 -> \"value4\"" << std::endl;
    o1 << "key6 -> \"\"" << std::endl;
    o2 << conf;

    EXPECT_EQ(o1.str(), o2.str());
}
