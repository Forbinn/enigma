#include "Rotors.hpp"

bool Enigma::Rotors::isValid() const
{
    return std::all_of(_rotors.begin(), _rotors.end(),
                       [](const auto & rotor){ return rotor.isValid(); });
}

Enigma::value_type Enigma::Rotors::convert(value_type c)
{
    if (!isValid())
        return {};

    _rotateRotors();

    for (auto itr = _rotors.begin(); itr != _rotors.end(); ++itr)
        c = itr->convertFromInput(c);

    c = _reflector.map(c);

    for (auto itr = _rotors.rbegin(); itr != _rotors.rend(); ++itr)
        c = itr->convertToInput(c);

    return c;
}

void Enigma::Rotors::reset()
{
    for (auto & rotor : _rotors)
        rotor.reset();
}

void Enigma::Rotors::_rotateRotors()
{
    for (auto & rotor : _rotors)
        if (rotor.rotate() == 0)
            break;
}
