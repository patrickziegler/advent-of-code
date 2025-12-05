#include <algorithm>
#include <cmath>
#include <fstream>

#include <gtest/gtest.h>

auto output_joltage(const std::string& item, const std::string::const_iterator& it1, const size_t count) -> size_t {
    if (count == 0) { return 0; }
    const auto it2 = std::max_element(it1, item.end() - count + 1);
    return (*it2 - '0') * std::pow(10, count - 1) + output_joltage(item, it2 + 1, count - 1);
}

auto total_output_joltage(std::istream& input, size_t count) {
    size_t result = 0;
    std::string item;
    while (std::getline(input, item)) {
        result += output_joltage(item, item.begin(), count);
    }
    return result;
}

class Aoc25Day3 : public testing::Test {
};

TEST_F(Aoc25Day3, Example1) {
    std::stringstream input{"987654321111111\n811111111111119\n234234234234278\n818181911112111"};
    size_t result = total_output_joltage(input, 2);
    ASSERT_EQ(result, 357ULL);
}

TEST_F(Aoc25Day3, Example2) {
    std::stringstream input{"987654321111111\n811111111111119\n234234234234278\n818181911112111"};
    size_t result = total_output_joltage(input, 12);
    ASSERT_EQ(result, 3121910778619ULL);
}

TEST_F(Aoc25Day3, Challenge1) {
    std::fstream input{"day3_input_banks.txt"};
    size_t result = total_output_joltage(input, 2);
    ASSERT_EQ(result, 17321ULL);
}

TEST_F(Aoc25Day3, Challenge2) {
    std::fstream input{"day3_input_banks.txt"};
    size_t result = total_output_joltage(input, 12);
    ASSERT_EQ(result, 171989894144198ULL);
}
