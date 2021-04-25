#pragma once

#include <vector>

#include "enigma_global.hpp"
#include "Rotor.hpp"
#include "Reflector.hpp"

namespace Enigma
{
class ENIGMA_EXPORT Rotors
{
public:
    using container = std::vector<Rotor>;

public:
    Rotors() = default;

    bool isValid() const;

public:
    value_type convert(value_type c);

public:
    void reset();

private:
    void _rotateRotors();

private:
    container _rotors;
    Reflector _reflector;
};
} // !namespace Enigma
