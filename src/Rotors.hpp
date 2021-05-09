#pragma once

#include <vector>
#include <list>

#include "enigma_global.hpp"
#include "Rotor.hpp"
#include "Reflector.hpp"

namespace Enigma
{
class ENIGMA_EXPORT Rotors
{
public:
    using container = std::list<Rotor>;

public:
    Rotors() = default;
    Rotors(const string & inputAlphabet,
           const string & outputAlphabet);

    bool isValid() const { return _isValid; }

public:
    void setInputAlphabet(const string & inputAlphabet);
    const string & inputAlphabet() const  { return _inputAlphabet; }
    void setOutputAlphabet(const string & outputAlphabet);
    const string & outputAlphabet() const { return _outputAlphabet; }

    void setIntermediateAlphabets(const std::vector<string> & alphabets);
    void appendIntermediateAlphabet(const string & alphabet);
    void prependIntermediateAlphabet(const string & alphabet);
    void insertIntermediateAlphabet(const string & alphabet, std::size_t index);
    void removeIntermediateAlphabet(std::size_t index);

    string intermediateAlphabet(std::size_t index) const;
    std::size_t intermediateAlphabetCount() const;
    std::vector<string> intermediateAlphabets() const;

    // TODO: create a setupAllAlphabets like function that sets input, intermediate and output alphabets at once

public:
    void setRotorsOffset(const std::vector<std::size_t> & offsets);
    void setRotorOffset(std::size_t offset, std::size_t index);

    std::size_t rotorOffset(std::size_t index) const;
    std::vector<std::size_t> rotorsOffset() const;
    std::size_t rotorCount() const { return _rotors.size(); }

public:
    value_type convert(value_type c);

public:
    void clear();
    void clearIntermediateAlphabet();
    void reset();

private:
    void _rotateRotors();
    void _refreshIsValid();

private:
    string    _inputAlphabet;
    string    _outputAlphabet;

    container _rotors;
    Reflector _reflector;

    bool      _isValid = false;
};
} // !namespace Enigma
