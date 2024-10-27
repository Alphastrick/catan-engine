#pragma once

#include <ostream>

namespace catan_engine::map {

class tile {

public:

    tile(char type);

    // tile(tile &&) = delete;
    // tile(const tile &) = delete;
    // tile& operator=(const tile &) = delete;
    // tile& operator=(const tile &&) = delete;

    char get_type() const;

private:

    char m_type;

};

std::ostream& operator<<(std::ostream& strm, const tile& _tile);

}
