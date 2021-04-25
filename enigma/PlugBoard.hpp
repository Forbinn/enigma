#pragma once

#include "enigma_global.hpp"

#include <unordered_map>

namespace Enigma
{
class ENIGMA_EXPORT PlugBoard
{
public:
    using container = std::unordered_map<value_type, value_type>;

public:
    PlugBoard() = default;

    const container & mapping() const { return _mapping; }

    void addMapping(value_type v1, value_type v2);
    void removeMapping(value_type v);

public:
    value_type map(value_type v) const;

public:
    void clear();

private:
    container _mapping;
};
} // !namespace Enigma
