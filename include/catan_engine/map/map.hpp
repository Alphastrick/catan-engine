#pragma once

#include <array>
#include <ostream>
#include <catan_engine/map/tile.hpp>

namespace catan_engine::map {

class map {

public:

    struct coordinate {
        size_t x;
        size_t y;

        bool is_valid() const;
    };

    static constexpr coordinate invalid_coordinate { static_cast<size_t>(-1), static_cast<size_t>(-1) };

    explicit map(const size_t width, const size_t height);
    ~map();

    map(map &&) = delete;
    map(const map &) = delete;
    map& operator=(const map &) = delete;
    map& operator=(const map &&) = delete;

    tile& get_tile(const coordinate& coord);
    tile& get_tile(const coordinate& coord) const;
    const std::array<coordinate, 6> get_neighbors(const coordinate& coord) const;

    const size_t get_width() const;
    const size_t get_height() const;


private:

    size_t get_index(const coordinate& coord) const;
    coordinate get_coordinates(const size_t index) const;
    bool is_index_valid(const size_t index) const;

    const size_t m_width, m_height;
    tile** m_tiles;

};

std::ostream& operator<<(std::ostream& strm, const map& _map);

}
