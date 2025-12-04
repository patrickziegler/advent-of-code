#include <fstream>

#include <gtest/gtest.h>

inline auto check_neighbor(const char& c) {
    return c == '@' || c == 'x';
}

class FloorPlan {
public:
    FloorPlan(std::istream& input) {
        std::string line;
        while (std::getline(input, line)) {
            m_floorPlan.emplace_back(std::move(line));
        }
    }
    auto countAccessiblePaperRolls() {
        size_t n_accessible = 0;
        size_t n_neigh;
        for (int i=0; i < m_floorPlan.size(); ++i) {
            for (int j=0; j < m_floorPlan[i].size(); ++j) {
                n_neigh = 0;
                if (i - 1 >= 0) {
                    // prev row
                    if (j - 1 >= 0) {
                        // left neigh
                        if (check_neighbor(m_floorPlan[i-1][j-1])) { ++n_neigh; }
                    }
                    if (j + 1 < m_floorPlan[i].size()) {
                        // right neigh
                        if (check_neighbor(m_floorPlan[i-1][j+1])) { ++n_neigh; }
                    }
                    if (check_neighbor(m_floorPlan[i-1][j])) { ++n_neigh; }
                }
                if (i + 1 < m_floorPlan.size()) {
                    // next row
                    if (j - 1 >= 0) {
                        // left neigh
                        if (check_neighbor(m_floorPlan[i+1][j-1])) { ++n_neigh; }
                    }
                    if (j + 1 < m_floorPlan[i].size()) {
                        // right neigh
                        if (check_neighbor(m_floorPlan[i+1][j+1])) { ++n_neigh; }
                    }
                    if (check_neighbor(m_floorPlan[i+1][j])) { ++n_neigh; }
                }
                // current row
                if (j - 1 >= 0) {
                    // left neigh
                    if (check_neighbor(m_floorPlan[i][j-1])) { ++n_neigh; }
                }
                if (j + 1 < m_floorPlan[i].size()) {
                    // right neigh
                    if (check_neighbor(m_floorPlan[i][j+1])) { ++n_neigh; }
                }
                if (m_floorPlan[i][j] == '@' && n_neigh < 4) {
                    m_floorPlan[i][j] = 'x'; // mark paper roll as removable
                    ++n_accessible;
                }
            }
        }
        return n_accessible;
    }
    void removeAccessiblePaperRolls() {
        for (int i=0; i < m_floorPlan.size(); ++i) {
            for (int j=0; j < m_floorPlan[i].size(); ++j) {
                if (m_floorPlan[i][j] == 'x') {
                    m_floorPlan[i][j] = '.';
                }
            }
        }
    }
private:
    std::vector<std::string> m_floorPlan;
};

class Aoc25Day4 : public testing::Test {
};

TEST_F(Aoc25Day4, Example1) {
    std::stringstream input{"..@@.@@@@.\n@@@.@.@.@@\n@@@@@.@.@@\n@.@@@@..@.\n@@.@@@@.@@\n.@@@@@@@.@\n.@.@.@.@@@\n@.@@@.@@@@\n.@@@@@@@@.\n@.@.@@@.@."};
    FloorPlan fp{input};
    size_t result = fp.countAccessiblePaperRolls();
    ASSERT_EQ(result, 13ULL);
}

TEST_F(Aoc25Day4, Example2) {
    std::stringstream input{"..@@.@@@@.\n@@@.@.@.@@\n@@@@@.@.@@\n@.@@@@..@.\n@@.@@@@.@@\n.@@@@@@@.@\n.@.@.@.@@@\n@.@@@.@@@@\n.@@@@@@@@.\n@.@.@@@.@."};
    FloorPlan fp{input};
    size_t result = 0;
    size_t round;
    while ((round = fp.countAccessiblePaperRolls())) {
        result += round;
        fp.removeAccessiblePaperRolls();
    }
    ASSERT_EQ(result, 43ULL);
}

TEST_F(Aoc25Day4, Challenge1) {
    std::fstream input{"day4_input_paper_rolls.txt"};
    FloorPlan fp{input};
    size_t result = fp.countAccessiblePaperRolls();
    ASSERT_EQ(result, 1480ULL);
}

TEST_F(Aoc25Day4, Challenge2) {
    std::fstream input{"day4_input_paper_rolls.txt"};
    FloorPlan fp{input};
    size_t result = 0;
    size_t round;
    while ((round = fp.countAccessiblePaperRolls())) {
        result += round;
        fp.removeAccessiblePaperRolls();
    }
    ASSERT_EQ(result, 8899ULL);
}
