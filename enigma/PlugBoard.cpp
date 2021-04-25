#include "PlugBoard.hpp"

void Enigma::PlugBoard::addMapping(value_type v1, value_type v2)
{
    if (v1 == v2)
        return ;

    _mapping[v1] = v2;
    _mapping[v2] = v1;
}

void Enigma::PlugBoard::removeMapping(value_type v)
{
    const auto itr = _mapping.find(v);
    if (itr == _mapping.end())
        return ;

    const auto itrMap = _mapping.find(itr->second);
    _mapping.erase(itr);
    _mapping.erase(itrMap);
}

Enigma::value_type Enigma::PlugBoard::map(value_type v) const
{
    const auto itr = _mapping.find(v);
    return itr == _mapping.end() ? v : itr->second;
}

void Enigma::PlugBoard::clear()
{
    _mapping.clear();
}
