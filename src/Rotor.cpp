#include <algorithm>

#include "Rotor.hpp"

Enigma::Rotor::Rotor(const string & alphabet)
{
    setAlphabet(alphabet);
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

void Enigma::Rotor::setRotation(std::size_t rotation)
{
    if (!isValid())
        return ;

    const auto oldRotation = _rotation;
    _rotation = rotation % _wires.size();
    _rotateWires(static_cast<int>(_rotation) - static_cast<int>(oldRotation));
}

bool Enigma::Rotor::rotate(bool forward)
{
    if (!isValid())
        return false;

    _rotateWires(forward ? 1 : -1);
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

    const auto wire   = _wires.at(idx).first;
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

    const auto wire   = _wires.at(idx).second;
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

    _rotateWires(-static_cast<int>(_rotation));
    _rotation = 0;
}

void Enigma::Rotor::_rotateWires(int count)
{
    if (count == 0)
        return ;
    else if (count < 0)
        count = static_cast<int>(_wires.size()) - (-count) % static_cast<int>(_wires.size());
    else
        count %= _wires.size();

    std::rotate(_wires.begin(), std::next(_wires.begin(), count), _wires.end());
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
