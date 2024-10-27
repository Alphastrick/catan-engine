#pragma once

#include <array>
#include <ostream>
#include <catan_engine/map/tile.hpp>

namespace catan_engine::map {

class map {

public:

    explicit map(const size_t width, const size_t height);
    ~map();

    map(map &&) = delete;
    map(const map &) = delete;
    map& operator=(const map &) = delete;
    map& operator=(const map &&) = delete;

    tile& get_tile(const size_t x, const size_t y);
    tile& get_tile(const size_t x, const size_t y) const;
    const std::array<size_t, 6> get_neighbors(const size_t x, const size_t y) const;

    const size_t get_width() const;
    const size_t get_height() const;

    size_t get_index(const size_t x, const size_t y) const;
    std::tuple<size_t, size_t> get_coordinates(const size_t index) const;

    bool is_index_valid(const size_t index) const;

private:

    const size_t m_width, m_height;
    tile** m_tiles;

};

std::ostream& operator<<(std::ostream& strm, const map& _map);

}
