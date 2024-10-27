#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <catan_engine/map/map.hpp>
#include <vector>

namespace catan_engine::map {

struct test_map_neighbors_param {
    std::tuple<size_t, size_t> size;
    map::coordinate coords;
    std::array<map::coordinate, 6> expected;

};

class test_map_neighbors : public testing::TestWithParam<test_map_neighbors_param> {};

TEST_P(test_map_neighbors, test_neighbors)
{
    const auto& param = GetParam();
    const auto [width, height] = param.size;
    
    map _map(width, height);
    
    const auto actual = _map.get_neighbors(param.coords);
    for (size_t i = 0; i < 6; i++)
    {
        EXPECT_EQ(actual[i].x, param.expected[i].x) << "Index " << i;
        EXPECT_EQ(actual[i].y, param.expected[i].y) << "Index " << i;
    }
}

INSTANTIATE_TEST_SUITE_P(
    test_neighbors,
    test_map_neighbors,
    testing::Values(
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 0 },
            { map::invalid_coordinate, map::invalid_coordinate, map::invalid_coordinate, map::coordinate{ 1, 0 }, map::invalid_coordinate, map::coordinate{ 0, 1 } }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 0 },
            { map::invalid_coordinate, map::invalid_coordinate, map::coordinate{ 1, 0 }, map::invalid_coordinate, map::coordinate{ 1, 1 }, map::coordinate{ 2, 1 } }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 1 },
            { map::coordinate{ 0, 0 }, map::coordinate{ 1, 0 }, map::invalid_coordinate, map::coordinate{ 1, 1 }, map::coordinate{ 0, 2 }, map::coordinate{ 1, 2 } }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 1, 1 },
            { map::coordinate{ 1, 0 }, map::coordinate{ 2, 0 }, map::coordinate{ 0, 1 }, map::coordinate{ 2, 1 }, map::coordinate{ 1, 2 }, map::coordinate{ 2, 2 } }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 1 },
            { map::coordinate{ 2, 0 }, map::invalid_coordinate, map::coordinate{ 1, 1 }, map::invalid_coordinate, map::coordinate{ 2, 2 }, map::invalid_coordinate }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 2 },
            { map::invalid_coordinate, map::coordinate{ 0, 1 }, map::invalid_coordinate, map::coordinate{ 1, 2 }, map::invalid_coordinate, map::coordinate{ 0, 3 } }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 1, 2 },
            { map::coordinate{ 0, 1 }, map::coordinate{ 1, 1 }, map::coordinate{ 0, 2 }, map::coordinate{ 2, 2 }, map::coordinate{ 0, 3 }, map::coordinate{ 1, 3 } }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 2 },
            { map::coordinate{ 1, 1 }, map::coordinate{ 2, 1 }, map::coordinate{ 1, 2 }, map::invalid_coordinate, map::coordinate{ 1, 3 }, map::coordinate{ 2, 3 } }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 0, 3 },
            { map::coordinate{ 0, 2 }, map::coordinate{ 1, 2 }, map::invalid_coordinate, map::coordinate{ 1, 3 }, map::invalid_coordinate, map::invalid_coordinate }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 1, 3 },
            { map::coordinate{ 1, 2 }, map::coordinate{ 2, 2 }, map::coordinate{ 0, 3 }, map::coordinate{ 2, 3 }, map::invalid_coordinate, map::invalid_coordinate }
        },
        test_map_neighbors_param{
            { 3, 4 },
            { 2, 3 },
            { map::coordinate{ 2, 2 }, map::invalid_coordinate, map::coordinate{ 1, 3 }, map::invalid_coordinate, map::invalid_coordinate, map::invalid_coordinate }
        }
    )
);

}
