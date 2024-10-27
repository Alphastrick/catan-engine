#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <catan_engine/map/map.hpp>
#include <vector>

namespace catan_engine::map {

struct test_map_neighbors_param {
    std::tuple<size_t, size_t> size;
    std::tuple<size_t, size_t> coords;
    std::array<size_t, 6> expected;

};

class test_map_neighbors : public testing::TestWithParam<test_map_neighbors_param> {};

TEST_P(test_map_neighbors, test_neighbors)
{
    const auto& param = GetParam();
    const auto [width, height] = param.size;
    const auto [x, y] = param.coords;
    
    map _map(width, height);
    
    const auto actual = _map.get_neighbors(x, y);
    for (size_t i = 0; i < 6; i++)
    {
        EXPECT_EQ(actual[i], param.expected[i]) << "Index " << i;
    }
}

INSTANTIATE_TEST_SUITE_P(
    test_neighbors,
    test_map_neighbors,
    testing::Values(
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 0 },
            { -1llu, -1llu, -1llu, 1, -1llu, 3 }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 0 },
            { -1llu, -1llu, 1, -1llu, 4, 5 }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 1 },
            { 0, 1, -1llu, 4, 6, 7 }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 1, 1 },
            { 1, 2, 3, 5, 7, 8 }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 1 },
            { 2, -1llu, 4, -1llu, 8, -1llu }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 2 },
            { -1llu, 3, -1llu, 7, -1llu, 9 }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 1, 2 },
            { 3, 4, 6, 8, 9, 10 }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 2 },
            { 4, 5, 7, -1llu, 10, 11 }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 3 },
            { 6, 7, -1llu, 10, -1llu, -1llu }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 1, 3 },
            { 7, 8, 9, 11, -1llu, -1llu }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 3 },
            { 8, -1llu, 10, -1llu, -1llu, -1llu }
        }
    )
);

}
