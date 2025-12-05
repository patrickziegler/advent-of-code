#include <algorithm>
#include <fstream>

#include <gtest/gtest.h>

auto read_ranges(std::istream& input) {
    std::vector<std::pair<size_t,size_t>> ranges_unsort;
    std::string item;
    size_t a, b;
    char c;
    while (std::getline(input, item)) {
        if (item == "") {
            break;
        }
        std::stringstream ss{item};
        ss >> a >> c >> b;
        ranges_unsort.emplace_back(a, b);
    }
    std::sort(ranges_unsort.begin(), ranges_unsort.end());
    decltype(ranges_unsort) ranges;
    bool merged;
    for (const auto& [a, b] : ranges_unsort) {
        merged = false;
        for (size_t i=0; i < ranges.size(); ++i) {
            if (a >= ranges[i].first && a <= ranges[i].second) {
                if (b > ranges[i].second) {
                    ranges[i].second = b;
                }
                merged = true;
                break;
            }
        }
        if (!merged) {
            ranges.emplace_back(a, b);
        }
    }
    return ranges;
}

auto count_fresh_items(std::istream& input) {
    const auto ranges = read_ranges(input);
    std::string item;
    size_t number;
    size_t result = 0;
    while (std::getline(input, item)) {
        number = std::stoull(item);
        for (const auto& [a, b] : ranges) {
            if (number >= a && number <= b) {
                ++result;
                break;
            }
        }
    }
    return result;
}

auto max_numer_of_fresh_items(std::istream& input) {
    const auto ranges = read_ranges(input);
    size_t result = 0;
    for (const auto& [a, b] : ranges) {
        result += b - a + 1;
    }
    return result;
}

class Aoc25Day5 : public testing::Test {
};

TEST_F(Aoc25Day5, Example1) {
    std::stringstream input{"3-5\n10-14\n16-20\n12-18\n\n1\n5\n8\n11\n17\n32"};
    size_t result = count_fresh_items(input);
    ASSERT_EQ(result, 3ULL);
}

TEST_F(Aoc25Day5, Example2) {
    std::stringstream input{"3-5\n10-14\n16-20\n12-18\n\n1\n5\n8\n11\n17\n32"};
    size_t result = max_numer_of_fresh_items(input);
    ASSERT_EQ(result, 14ULL);
}

TEST_F(Aoc25Day5, Challenge1) {
    std::fstream input{"day5_input_database.txt"};
    size_t result = count_fresh_items(input);
    ASSERT_EQ(result, 661ULL);
}

TEST_F(Aoc25Day5, Challenge2) {
    std::fstream input{"day5_input_database.txt"};
    size_t result = max_numer_of_fresh_items(input);
    ASSERT_EQ(result, 359526404143208ULL);
}
