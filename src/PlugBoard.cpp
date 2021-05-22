#include "PlugBoard.hpp"

bool Enigma::PlugBoard::isValidForAlphabet(const string & alphabet) const
{
    // All mapping values must appear in the alphabet for it to be valid
    for (const auto & p : _mapping)
        if (alphabet.find(p.first) == string::npos)
            return false;

    return true;
}

std::size_t Enigma::PlugBoard::mappingCount() const
{
    return _mapping.size() / 2;
}

void Enigma::PlugBoard::setMapping(const Enigma::PlugBoard::container & mapping)
{
    for (const auto & p : mapping)
        addMapping(p.first, p.second);
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

void Enigma::PlugBoard::_addMappingImpl(Enigma::value_type v1, Enigma::value_type v2)
{
    if (v1 == v2)
        return ;

    removeMapping(v1);
    removeMapping(v2);

    _mapping[v1] = v2;
    _mapping[v2] = v1;
}

void Enigma::PlugBoard::_removeMappingImpl(Enigma::value_type v)
{
    const auto itr = _mapping.find(v);
    if (itr == _mapping.end())
        return ;

    const auto itrMap = _mapping.find(itr->second);
    _mapping.erase(itr);
    _mapping.erase(itrMap);
}
