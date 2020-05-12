#include <algorithm>
#include <vector>
#include <utility>

#include <catch2/catch.hpp>

#include "../Merge.h"

TEST_CASE("Merge", "[]") {
    std::vector<std::pair<int, int>> a = {{1, 1},
                                          {2, 2},
                                          {3, 3}};
    std::vector<std::pair<int, int>> b = {{1, 2},
                                          {2, 3}};

    std::vector<std::pair<int, int>> c = {{1, 1},
                                          {1, 2},
                                          {2, 2},
                                          {2, 3},
                                          {3, 3}};

    std::vector<std::pair<int, int>> dst;
    std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(dst));
    REQUIRE(c == dst);
    dst.clear();
    rdm::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(dst));
    REQUIRE(c == dst);
}
