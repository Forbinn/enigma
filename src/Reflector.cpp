#include "Reflector.hpp"

Enigma::Reflector::Reflector()
    : Rotor { false }
{
}

Enigma::Reflector::Reflector(const Enigma::string & alphabet)
    : Rotor { false }
{
    setAlphabet(alphabet);
}

bool Enigma::Reflector::isValid() const
{
    return Rotor::isValid() && _wires.size() % 2 == 0;
}

bool Enigma::Reflector::rotate(bool)
{
    // Calling rotate on a reflector is a no-op
    return false;
}
