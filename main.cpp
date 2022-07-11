#include <iostream>
#include <vector>
#include <CLI/CLI.hpp>
#include <random>
#include <sstream>
#include <unordered_set>

#include <adjective.hpp>
#include <noun.hpp>


std::random_device dv;
std::mt19937 engine(dv());
std::uniform_int_distribution<int> r(0, std::numeric_limits<int>::max());

std::unordered_set<std::string> set;

std::string generate(bool suffix, bool filter)
{
    for(int i=0; i< 1000; i++){
        const auto& adj = adjective.at(r(engine)%adjective.size());
        const auto& n = noun.at(r(engine)%noun.size());
        std::stringstream result;
        result << adj;
        result << "-";
        result << n;
        if(suffix){
            auto suffix_number = r(engine);
            result << "-";
            result << std::setw(4) <<std::setfill('0') << suffix_number%10000;
        }
        auto result_str = result.str();
        if(filter){
            if(set.contains(result_str)){
                continue;
            }
            set.insert(result_str);
        }
        return result_str;
    }
    return "We loop for 1000 times but still found duplicated value, please consider enlarge your dataset";
}

int main(int argc, char *argv[])
{
    CLI::App app{"This is a name generator for easy life. It will generate random names for you."};
    std::size_t number = 1;
    bool suffix = false;
    bool filter = false;
    app.add_option("number", number, "The number of names generated");
    app.add_option("--suffix", suffix, "If the name should add suffix which are numbers");
    app.add_option("--filter", filter, "If the generator should filter the duplicated value");
    CLI11_PARSE(app, argc, argv);

    set.reserve(number);

    for(std::size_t i=0; i<number; i++){
        std::cout << generate(suffix, filter) << std::endl;
    }

    return 0;
}