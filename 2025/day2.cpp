#include <fstream>

#include <gtest/gtest.h>

using Ranges = std::vector<std::pair<size_t,size_t>>;

auto parse_ranges(std::istream& input) {
    Ranges ranges;
    std::string item;
    while (std::getline(input, item, ',')) {
        auto pos = item.find('-');
        ranges.emplace_back(
                    std::stoull(item.substr(0, pos)),
                    std::stoull(item.substr(pos + 1)));
    }
    return ranges;
}

auto is_duplicate(std::string_view id) {
    if (id.size() % 2 != 0) {
        return false;
    }
    return id.substr(0, id.size() / 2) == id.substr(id.size() / 2, id.size() / 2);
}

auto is_multiple(std::string_view id) {
    for (size_t i=2; i <= id.size(); ++i) {
        if (id.size() % i) {
            continue;
        }
        const auto len = id.size() / i;
        bool ok = true;
        for (size_t j=1; j < i; ++j) {
            if (id.substr(0, len) != id.substr(j * len, len)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return true;
        }
    }
    return false;
}

template <typename Validator>
auto sum_invalid_ids(const Ranges& ranges, Validator validate) {
    size_t result = 0;
    for (auto [a, b] : ranges) {
        for (; a <= b; ++a) {
            if (validate(std::to_string(a))) {
                result += a;
            }
        }
    }
    return result;
}

class Aoc25Day2 : public testing::Test {
};

TEST_F(Aoc25Day2, Example1) {
    std::stringstream input{"11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124"};
    const auto ranges = parse_ranges(input);
    const auto result = sum_invalid_ids(ranges, is_duplicate);
    ASSERT_EQ(result, 1227775554ULL);
}

TEST_F(Aoc25Day2, Example2) {
    std::stringstream input{"11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124"};
    const auto ranges = parse_ranges(input);
    const auto result = sum_invalid_ids(ranges, is_multiple);
    ASSERT_EQ(result, 4174379265ULL);
}

TEST_F(Aoc25Day2, Challenge1) {
    std::ifstream input{"day2_input_ranges.txt"};
    const auto ranges = parse_ranges(input);
    const auto result = sum_invalid_ids(ranges, is_duplicate);
    ASSERT_EQ(result, 53420042388ULL);
}

TEST_F(Aoc25Day2, Challenge2) {
    std::ifstream input{"day2_input_ranges.txt"};
    const auto ranges = parse_ranges(input);
    const auto result = sum_invalid_ids(ranges, is_multiple);
    ASSERT_EQ(result, 69553832684ULL);
}
