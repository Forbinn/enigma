#pragma once

#include "enigma_global.hpp"

namespace Enigma
{
class ENIGMA_EXPORT Rotor
{
public:
    Rotor() = default;
    Rotor(const string & input,
          const string & output);

    bool isValid() const { return _isValid; }

    const string & inputAlphabet() const  { return _inputAlphabet; }
    const string & outputAlphabet() const { return _outputAlphabet; }
    void setInputAlphabet(const string & input);
    void setOutputAlphabet(const string & output);

    std::size_t offset() const { return _offset; }
    void setOffset(std::size_t offset);
    int rotate(int step = 1);

public:
    value_type convertFromInput(value_type c) const;
    value_type convertToInput(value_type c) const;

public:
    void clear();
    void reset();

private:
    void _refreshIsValid();

private:
    string      _inputAlphabet;
    string      _outputAlphabet;
    std::size_t _offset = 0;
    bool        _isValid = false;
};
} // !namespace Enigma
