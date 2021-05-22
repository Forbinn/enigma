#pragma once

#include <unordered_map>

#include "enigma_global.hpp"

namespace Enigma
{
class ENIGMA_EXPORT PlugBoard
{
public:
    struct Plug
    {
        Plug(PlugBoard & b, value_type v);

        operator value_type() const { return board.map(value); }
        Plug & operator=(value_type v);

        PlugBoard & board;
        value_type  value;
    };

public:
    using container = std::unordered_map<value_type, value_type>;

public:
    PlugBoard() = default;

    bool isValidForAlphabet(const string & alphabet) const;

    const container & mapping() const { return _mapping; }
    std::size_t mappingCount() const;

    void setMapping(const container & mapping);
    template<typename ... Args>
    void addMapping(value_type v1, value_type v2, Args && ... args)
    {
        static_assert(sizeof...(args) % 2 == 0, "The number of argument must be even");

        _addMappingImpl(v1, v2);
        if constexpr (sizeof...(args) > 0)
            addMapping(std::forward<Args>(args)...);
    }
    template<typename ... Args>
    void removeMapping(value_type v, Args && ... args)
    {
        _removeMappingImpl(v);
        if constexpr (sizeof...(args) > 0)
            removeMapping(std::forward<Args>(args)...);
    }

public:
    Plug operator[](value_type v)             { return { *this, v }; }
    value_type operator[](value_type v) const { return map(v); }

public:
    value_type map(value_type v) const;

public:
    void clear();

private:
    void _addMappingImpl(value_type v1, value_type v2);
    void _removeMappingImpl(value_type v);

private:
    container _mapping;
};
} // !namespace Enigma
