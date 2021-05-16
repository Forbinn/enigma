#include <algorithm>

#include "Rotors.hpp"

bool Enigma::Rotors::isValid() const
{
    if (_rotors.empty() || !_reflector.isValid())
        return false;

    return std::all_of(_rotors.begin(), _rotors.end(),
                       [](const auto & rotor){ return rotor.isValid(); });
}

Enigma::Rotor & Enigma::Rotors::appendRotor(const string & alphabet)
{
    return insertRotor(_rotors.size(), alphabet);
}

Enigma::Rotor & Enigma::Rotors::prependRotor(const string & alphabet)
{
    return insertRotor(0, alphabet);
}

Enigma::Rotor & Enigma::Rotors::insertRotor(std::size_t idx, const string & alphabet)
{
    idx = std::clamp(0ul, idx, _rotors.size());
    if (idx == 0)
        _setNewInputAlphabet(alphabet);

    const auto itr = std::next(_rotors.begin(), static_cast<container::iterator::difference_type>(idx));
    return *_rotors.emplace(itr, alphabet);
}

void Enigma::Rotors::removeRotor(std::size_t idx)
{
    if (idx >= _rotors.size())
        return ;

    _rotors.erase(std::next(_rotors.begin(), static_cast<container::iterator::difference_type>(idx)));
}

Enigma::value_type Enigma::Rotors::convert(value_type c)
{
    if (!isValid())
        return {};

    if (!_isValueInAlphabet(c))
        return c;

    _rotateRotors();

    auto idx = _getIdxOfValue(c);
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
    const auto firstRotorHasCrossedANotch = _rotors.at(0).rotate();
    if (_rotors.size() == 1)
        return ;

    if (firstRotorHasCrossedANotch || _rotors.at(1).isInNotchPosition())
    {
        for (auto itr = std::next(_rotors.begin()); itr != _rotors.end(); ++itr)
            if (!itr->rotate())
                return ;
    }
}

void Enigma::Rotors::_setNewInputAlphabet(const Enigma::string & alphabet)
{
    _inputAlphabet = alphabet;
    std::sort(_inputAlphabet.begin(), _inputAlphabet.end());
}

bool Enigma::Rotors::_isValueInAlphabet(Enigma::value_type c) const
{
    return _inputAlphabet.find(c) != string::npos;
}

std::size_t Enigma::Rotors::_getIdxOfValue(value_type c) const
{
    return _inputAlphabet.find(c);
}

Enigma::value_type Enigma::Rotors::_getValueOfIdx(std::size_t idx) const
{
    return _inputAlphabet.at(idx);
}
