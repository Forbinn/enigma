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
    Rotor & appendRotor(const string & alphabet);
    Rotor & prependRotor(const string & alphabet);
    Rotor & insertRotor(std::size_t idx, const string & alphabet);
    void removeRotor(std::size_t idx);

    Rotor & rotor(std::size_t idx)             { return _rotors.at(idx); }
    const Rotor & rotor(std::size_t idx) const { return _rotors.at(idx); }

    std::size_t rotorCount() const { return _rotors.size(); }

    const string & inputAlphabet() const { return _inputAlphabet; }

public:
    Reflector & reflector()             { return _reflector; }
    const Reflector & reflector() const { return _reflector; }

    void setReflectorAlphabet(const string & alphabet) { _reflector.setAlphabet(alphabet); }

public:
    value_type convert(value_type c);

public:
    void clear();
    void reset();

private:
    void _rotateRotors();
    void _setNewInputAlphabet(const string & alphabet);

    bool _isValueInAlphabet(value_type c) const;

private:
    std::size_t _getIdxOfValue(value_type c) const;
    value_type _getValueOfIdx(std::size_t idx) const;

private:
    container _rotors;
    Reflector _reflector;

    string    _inputAlphabet;
};
} // !namespace Enigma