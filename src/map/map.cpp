#include <catan_engine/map/map.hpp>

#include <cassert>

namespace catan_engine::map {
    
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

tile& map::get_tile(const size_t x, const size_t y)
{
    const size_t index = get_index(x, y);
    return *m_tiles[index];
}

tile& map::get_tile(const size_t x, const size_t y) const
{
    const size_t index = get_index(x, y);
    return *m_tiles[index];
}

const std::array<size_t, 6> map::get_neighbors(const size_t x, const size_t y) const
{
    const size_t index = get_index(x, y);
    std::array<size_t, 6> neighbors = {};
    
    const size_t max_index = m_width * m_height;

    neighbors[2] = index - 1;
    neighbors[3] = index + 1;

    if (y % 2 == 1)
    {
        neighbors[0] = y == 0  ? -1llu : index - m_width;
        neighbors[1] = x >= m_width - 1 || y == 0 ? -1llu : index - m_width + 1;
        neighbors[4] = y >= m_height - 1 ? -1llu : index + m_width;
        neighbors[5] = x >= m_width - 1 || y >= m_height - 1 ? -1llu : index + m_width + 1;
    }
    else
    {
        neighbors[0] = x == 0 || y == 0 ? -1llu : index - m_width - 1;
        neighbors[1] = x >= m_width || y == 0 ? -1llu : index - m_width;
        neighbors[4] = x == 0 || y >= m_height - 1 ? -1llu : index + m_width - 1;
        neighbors[5] = x >= m_width || y >= m_height - 1 ? -1llu : index + m_width;
    }

    if (x == 0)
    {
        neighbors[2] = -1;
        neighbors[3] = index + 1;
    }
    else if (x == m_width - 1)
    {
        neighbors[2] = index - 1;
        neighbors[3] = -1llu;
    }

    if (y == 0)
    {
        neighbors[0] = -1llu;
        neighbors[1] = -1llu;
    }
    else if (y == m_height - 1)
    {
        neighbors[4] = -1llu;
        neighbors[5] = -1llu;
    }

    return neighbors;
}

const size_t map::get_width() const
{
    return m_width;
}

const size_t map::get_height() const
{
    return m_height;
}

size_t map::get_index(const size_t x, const size_t y) const
{
    assert(x < m_width && y < m_height);
    return m_width * y + x;
}

std::tuple<size_t, size_t> map::get_coordinates(const size_t index) const
{
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
            strm << _map.get_tile(x, y) << ' ';
        }
        strm << '\n';
    }
    return strm;
}

}
