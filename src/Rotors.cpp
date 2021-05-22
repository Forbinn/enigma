#include <algorithm>

#include "Rotors.hpp"

bool Enigma::Rotors::isValid() const
{
    if (_rotors.empty() || !_reflector.isValid())
        return false;

    return std::all_of(_rotors.begin(), _rotors.end(),
                       [](const auto & rotor){ return rotor.isValid(); });
}

Enigma::Rotor & Enigma::Rotors::appendRotor(string_view alphabet)
{
    return insertRotor(_rotors.size(), alphabet);
}

Enigma::Rotor & Enigma::Rotors::appendRotor(Rotor::Standard r)
{
    return insertRotor(_rotors.size(), r);
}

Enigma::Rotor & Enigma::Rotors::prependRotor(string_view alphabet)
{
    return insertRotor(0, alphabet);
}

Enigma::Rotor & Enigma::Rotors::prependRotor(Rotor::Standard r)
{
    return insertRotor(0, r);
}

Enigma::Rotor & Enigma::Rotors::insertRotor(std::size_t idx, string_view alphabet)
{
    idx = std::clamp<std::size_t>(0, idx, _rotors.size());
    if (idx == 0)
        _setNewInputAlphabet(alphabet);

    const auto itr = std::next(_rotors.begin(), static_cast<container::iterator::difference_type>(idx));
    return *_rotors.emplace(itr, alphabet);
}

Enigma::Rotor & Enigma::Rotors::insertRotor(std::size_t idx, Rotor::Standard r)
{
    idx = std::clamp<std::size_t>(0, idx, _rotors.size());
    if (idx == 0)
        _setNewInputAlphabet(Rotor::alphabetOfStandardRotor(r));

    const auto itr = std::next(_rotors.begin(), static_cast<container::iterator::difference_type>(idx));
    return *_rotors.emplace(itr, r);
}

void Enigma::Rotors::removeRotor(std::size_t idx)
{
    if (idx >= _rotors.size())
        return ;

    _rotors.erase(std::next(_rotors.begin(), static_cast<container::iterator::difference_type>(idx)));
}

void Enigma::Rotors::setReflector(Reflector::Standard r)
{
    _reflector = Reflector(r);
}

Enigma::value_type Enigma::Rotors::convert(value_type c)
{
    if (!isValid())
        return {};

    auto idx = _getIdxOfValue(c);
    if (idx == string::npos)
        return c;

    _rotateRotors();

    for (auto itr = _rotors.begin(); itr != _rotors.end(); ++itr)
        idx = itr->convertTo(idx);

    idx = _reflector.convert(idx);

    for (auto itr = _rotors.rbegin(); itr != _rotors.rend(); ++itr)
        idx = itr->convertFrom(idx);

    return _getValueOfIdx(idx);
}

void Enigma::Rotors::clear()
{
    _rotors.clear();
    _reflector.clear();
}

void Enigma::Rotors::reset()
{
    for (auto & rotor : _rotors)
        rotor.reset();
}

void Enigma::Rotors::_rotateRotors()
{
    const auto firstRotorHasCrossedANotch = _rotors.begin()->rotate();
    if (_rotors.size() == 1)
        return ;

    if (firstRotorHasCrossedANotch || std::next(_rotors.begin())->isInNotchPosition())
    {
        for (auto itr = std::next(_rotors.begin()); itr != _rotors.end(); ++itr)
            if (!itr->rotate())
                return ;
    }
}

void Enigma::Rotors::_setNewInputAlphabet(string_view alphabet)
{
    _inputAlphabet = alphabet;
    std::sort(_inputAlphabet.begin(), _inputAlphabet.end());
}

std::size_t Enigma::Rotors::_getIdxOfValue(value_type c) const
{
    return _inputAlphabet.find(c);
}

Enigma::value_type Enigma::Rotors::_getValueOfIdx(std::size_t idx) const
{
    return _inputAlphabet.at(idx);
}
