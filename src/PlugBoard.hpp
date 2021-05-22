#pragma once

#include <unordered_map>

#include "enigma_global.hpp"

namespace Enigma
{
class ENIGMA_EXPORT PlugBoard
{
public:
    using container = std::unordered_map<value_type, value_type>;

public:
    PlugBoard() = default;

    bool isValidForAlphabet(const string & alphabet) const;

    const container & mapping() const { return _mapping; }
    std::size_t mappingCount() const;

    void setMapping(const container & mapping);
    // TODO: create function to add / remove multiple mapping at the same time
    void addMapping(value_type v1, value_type v2);
    void removeMapping(value_type v);

    // TODO: create operator[] to get / set a mapping

public:
    value_type map(value_type v) const;

public:
    void clear();

private:
    container _mapping;
};
} // !namespace Enigma
