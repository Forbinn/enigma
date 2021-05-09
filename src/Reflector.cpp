#include "Reflector.hpp"

Enigma::Reflector::Reflector(const Enigma::string & alphabet)
    : _alphabet { alphabet }
{
}

bool Enigma::Reflector::isValid() const
{
    return !_alphabet.empty() && _alphabet.size() % 2 == 0;
}

void Enigma::Reflector::setAlphabet(const Enigma::string & alphabet)
{
    _alphabet = alphabet;
}

Enigma::value_type Enigma::Reflector::convert(Enigma::value_type c) const
{
    if (!isValid())
        return {};

    // Search the character in the alphabet and get its index
    // If we find it, then return the value at its opposing index
    // For an alphabet of 26 character here are some examples
    // idx == 0  -> opposite == 26
    // idx == 5  -> opposite == 20
    // idx == 9  -> opposite == 16
    // idx == 15 -> opposite == 10
    // idx == 13 -> opposite == 12
    const auto idx = _alphabet.find(c);
    return idx == string::npos ? c : _alphabet.at(_alphabet.size() - idx - 1);
}

void Enigma::Reflector::clear()
{
    _alphabet.clear();
}
