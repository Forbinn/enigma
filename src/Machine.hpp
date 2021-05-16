#pragma once

#include "enigma_global.hpp"
#include "Rotors.hpp"
#include "PlugBoard.hpp"

namespace Enigma
{
class ENIGMA_EXPORT Machine
{
public:
    Machine() = default;

    bool isValid() const;

public:
    Rotors & rotors()                   { return _rotors; }
    const Rotors & rotors() const       { return _rotors; }
    PlugBoard & plugboard()             { return _plugboard; }
    const PlugBoard & plugboard() const { return _plugboard; }

public:
    value_type convert(value_type v);
    string convert(const string & s);

public:
    void clear();
    void reset();

public:
    static Machine buildRandomMachine(const string & alphabet = "abcdefghijklmnopqrstuvwxyz",
                                      std::size_t rotorCount = 3,
                                      std::size_t plugboardSwap = 10);

private:
    Rotors    _rotors;
    PlugBoard _plugboard;
};
} // !namespace Enigma

