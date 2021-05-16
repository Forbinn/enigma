#include <algorithm>

#include "Rotor.hpp"

Enigma::Rotor::Rotor(const string & alphabet)
{
    setAlphabet(alphabet);
}

Enigma::Rotor::Rotor(bool allowStraightWire)
    : _allowStraightWire { allowStraightWire }
{
}

void Enigma::Rotor::setAlphabet(const string & alphabet)
{
    clear();

    string sortedAlphabet(alphabet);
    std::sort(sortedAlphabet.begin(), sortedAlphabet.end());

    _wires.resize(alphabet.size());

    for (std::size_t i = 0; i < alphabet.size(); ++i)
    {
        const auto & c  = alphabet.at(i);
        const auto idx  = sortedAlphabet.find(c);
        _wires[i].first = static_cast<int>(idx) - static_cast<int>(i);

        if (!_allowStraightWire && i == idx)
        {
            _wires.clear();
            return ;
        }
    }

    for (std::size_t i = 0; i < sortedAlphabet.size(); ++i)
    {
        const auto & c  = sortedAlphabet.at(i);
        const auto idx  = alphabet.find(c);
        _wires[i].second = static_cast<int>(idx) - static_cast<int>(i);
    }
}

void Enigma::Rotor::setNotches(const std::vector<std::size_t> & notches)
{
    _notches.clear();
    _notches.reserve(notches.size());
    for (const auto & notch : notches)
        addNotch(notch);
}

void Enigma::Rotor::addNotch(std::size_t idx)
{
    if (idx >= _wires.size())
        return ;

    const auto itr = std::find(_notches.begin(), _notches.end(), idx);
    if (itr == _notches.end())
        _notches.emplace_back(idx);
}

void Enigma::Rotor::removeNotch(std::size_t idx)
{
    const auto itr = std::find(_notches.begin(), _notches.end(), idx);
    if (itr != _notches.end())
        _notches.erase(itr);
}

bool Enigma::Rotor::isInNotchPosition() const
{
    return std::find(_notches.begin(), _notches.end(), _rotation) != _notches.end();
}

void Enigma::Rotor::setRotation(std::size_t rotation)
{
    if (!isValid())
        return ;

    _rotation = rotation % _wires.size();
}

bool Enigma::Rotor::rotate(bool forward)
{
    if (!isValid())
        return false;

    if (forward)
    {
        ++_rotation;
        if (_rotation >= _wires.size())
            _rotation -= _wires.size();
    }
    else
    {
        if (_rotation == 0)
            _rotation = _wires.size() - 1;
        else
            --_rotation;
    }

    return _hasCrossedANotch(forward);
}

std::size_t Enigma::Rotor::convertTo(std::size_t idx) const
{
    if (!isValid() || idx >= _wires.size())
        return string::npos;

    const auto wireIdx = [idx, this]
    {
        auto newIdx = idx + _rotation;
        if (newIdx >= _wires.size())
            newIdx -= _wires.size();
        return newIdx;
    }();

    const auto wire   = _wires.at(wireIdx).first;
    const auto result = wire + static_cast<int>(idx);

    if (result < 0)
        return static_cast<std::size_t>(static_cast<int>(_wires.size()) + result);
    else if (static_cast<std::size_t>(result) >= _wires.size())
        return static_cast<std::size_t>(result) - _wires.size();
    else
        return static_cast<std::size_t>(result);
}

std::size_t Enigma::Rotor::convertFrom(std::size_t idx) const
{
    if (!isValid())
        return string::npos;

    const auto wireIdx = [idx, this]
    {
        auto newIdx = idx + _rotation;
        if (newIdx >= _wires.size())
            newIdx -= _wires.size();
        return newIdx;
    }();

    const auto wire   = _wires.at(wireIdx).second;
    const auto result = wire + static_cast<int>(idx);

    if (result < 0)
        return static_cast<std::size_t>(static_cast<int>(_wires.size()) + result);
    else if (static_cast<std::size_t>(result) >= _wires.size())
        return static_cast<std::size_t>(result) - _wires.size();
    else
        return static_cast<std::size_t>(result);
}

void Enigma::Rotor::clear()
{
    _wires.clear();
    _notches.clear();
    _rotation = 0;
}

void Enigma::Rotor::reset()
{
    if (!isValid())
        return ;

    _rotation = 0;
}

bool Enigma::Rotor::_hasCrossedANotch(bool forward) const
{
    for (const auto & notch : _notches)
    {
        if (forward && (_rotation == notch + 1 || (notch == _wires.size() - 1 && _rotation == 0)))
            return true;
        else if (!forward && _rotation == notch)
            return true;
    }

    return false;
}
