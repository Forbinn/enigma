#pragma once

#include <unordered_map>

#include "enigma_global.hpp"

namespace Enigma
{
class ENIGMA_EXPORT Reflector
{
public:
    Reflector() = default;
    Reflector(const string & alphabet);

    bool isValid() const;

    const string & alphabet() const { return _alphabet; }
    void setAlphabet(const string & alphabet);

public:
    value_type convert(value_type c) const;

public:
    void clear();

private:
    string _alphabet;
};
} // !namespace Enigma
