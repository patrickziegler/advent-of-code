#include <cmath>
#include <fstream>

#include <gtest/gtest.h>

constexpr static const size_t DIAL_SIZE = 99 + 1;
constexpr static const size_t DIAL_START = 50;

class Dial {
public:
    auto dial(const std::string& instruction) -> size_t {
        // TODO: instruction sanity check
        auto distance = std::stoi(instruction.substr(1));
        if (instruction.at(0) == 'L') {
            distance *= -1;
        }
        return rotate(distance);
    }
    bool isZero() const {
        return m_state == 0;
    }
private:
    auto rotate(const int& distance) -> size_t {
        const int sign = static_cast<int>(std::copysign(1.0, distance));
        const int next_state = m_state + sign * (std::abs(distance) % DIAL_SIZE);
        const size_t rounds = std::abs(distance) / DIAL_SIZE;
        const size_t overshoot = ((next_state > (int) DIAL_SIZE || (m_state != 0 && next_state < 0)) ? 1 : 0);
        m_state = next_state;
        if (m_state < 0) {
            m_state += DIAL_SIZE;
        }
        m_state = m_state % DIAL_SIZE;
        return rounds + overshoot;
    }
    int m_state = DIAL_START;
};

class Aoc25Day1 : public testing::Test {
};

TEST_F(Aoc25Day1, Example1) {
    std::vector<std::string> instructions = {"L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"};
    size_t hitZero = 0;
    size_t crossZero = 0;
    Dial d;
    for (const auto& instruction : instructions) {
        crossZero += d.dial(instruction);
        if (d.isZero()) {
            ++hitZero;
        }
    }
    ASSERT_EQ(hitZero, 3);
    ASSERT_EQ(hitZero + crossZero, 6);
}

TEST_F(Aoc25Day1, Challenge1) {
    std::ifstream in{"day1_input_rotations.txt"};
    std::string instruction;
    size_t hitZero = 0;
    size_t crossZero = 0;
    Dial d;
    while (in >> instruction) {
        crossZero += d.dial(instruction);
        if (d.isZero()) {
            ++hitZero;
        }
    }
    ASSERT_EQ(hitZero, 1031);
    ASSERT_EQ(hitZero + crossZero, 5831);
}
