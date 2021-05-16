#pragma once

#include "Rotor.hpp"

namespace Enigma
{
class ENIGMA_EXPORT Reflector : public Rotor
{
public:
    Reflector();
    Reflector(const string & alphabet);

    bool isValid() const override;

public:
    bool rotate(bool = true) override;

public:
    std::size_t convertFrom(std::size_t idx) const override { return convertTo(idx); }
    std::size_t convert(std::size_t idx) const              { return convertTo(idx); }
};
} // !namespace Enigma
