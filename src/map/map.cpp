#include <catan_engine/map/map.hpp>

#include <cassert>

namespace catan_engine::map {
    
bool map::coordinate::is_valid() const
{
    return x != static_cast<size_t>(-1) && y != static_cast<size_t>(-1);
}


map::map(const size_t width, const size_t height)
    : m_width(width)
    , m_height(height)
{
    m_tiles = new tile*[m_width * m_height];
    for (size_t i = 0; i < m_width * m_height; i++)
    {
        m_tiles[i] = new tile('*');
    } 
}

map::~map()
{
    delete[] m_tiles;
}

tile& map::get_tile(const coordinate& coord)
{
    const size_t index = get_index(coord);
    return *m_tiles[index];
}

tile& map::get_tile(const coordinate& coord) const
{
    const size_t index = get_index(coord);
    return *m_tiles[index];
}

const std::array<map::coordinate, 6> map::get_neighbors(const coordinate& coord) const
{
    const auto [x, y] = coord;
    const size_t index = get_index(coord);
    std::array<size_t, 6> neighbor_indices = {};

    neighbor_indices[2] = index - 1;
    neighbor_indices[3] = index + 1;

    if (y % 2 == 1)
    {
        neighbor_indices[0] = y == 0  ? -1llu : index - m_width;
        neighbor_indices[1] = x >= m_width - 1 || y == 0 ? -1llu : index - m_width + 1;
        neighbor_indices[4] = y >= m_height - 1 ? -1llu : index + m_width;
        neighbor_indices[5] = x >= m_width - 1 || y >= m_height - 1 ? -1llu : index + m_width + 1;
    }
    else
    {
        neighbor_indices[0] = x == 0 || y == 0 ? -1llu : index - m_width - 1;
        neighbor_indices[1] = x >= m_width || y == 0 ? -1llu : index - m_width;
        neighbor_indices[4] = x == 0 || y >= m_height - 1 ? -1llu : index + m_width - 1;
        neighbor_indices[5] = x >= m_width || y >= m_height - 1 ? -1llu : index + m_width;
    }

    if (x == 0)
    {
        neighbor_indices[2] = -1;
        neighbor_indices[3] = index + 1;
    }
    else if (x == m_width - 1)
    {
        neighbor_indices[2] = index - 1;
        neighbor_indices[3] = -1llu;
    }

    if (y == 0)
    {
        neighbor_indices[0] = -1llu;
        neighbor_indices[1] = -1llu;
    }
    else if (y == m_height - 1)
    {
        neighbor_indices[4] = -1llu;
        neighbor_indices[5] = -1llu;
    }


    std::array<coordinate, 6> neighbors = {};
    for (size_t i = 0; i < 6; i++)
    {
        neighbors[i] = get_coordinates(neighbor_indices[i]);
    }

    return neighbors;
}

size_t map::get_width() const
{
    return m_width;
}

size_t map::get_height() const
{
    return m_height;
}

size_t map::get_index(const coordinate& coord) const
{
    assert(coord.x < m_width && coord.y < m_height);
    return m_width * coord.y + coord.x;
}

map::coordinate map::get_coordinates(const size_t index) const
{
    if (index == static_cast<size_t>(-1))
    {
        return invalid_coordinate;
    }
    
    const size_t x = index % m_width;
    const size_t y = (index - x) / m_width;
    return { x, y };
}

bool map::is_index_valid(const size_t index) const
{
    return index < m_width * m_height;
}

std::ostream& operator<<(std::ostream& strm, const map& _map)
{
    for (size_t y = 0; y < _map.get_height(); y++)
    {
        if (y % 2 == 0) {
            strm << ' ';
        }
        for (size_t x = 0; x < _map.get_width(); x++)
        {
            strm << _map.get_tile({x, y}) << ' ';
        }
        strm << '\n';
    }
    return strm;
}

}
