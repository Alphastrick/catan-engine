#include <catan_engine/map/tile.hpp>

namespace catan_engine::map {
    
tile::tile(const char type)
    : m_type(type)
{}

char tile::get_type() const
{
    return m_type;
}

std::ostream& operator<<(std::ostream& strm, const tile& _tile)
{
    strm << _tile.get_type();
    return strm;
}

}
