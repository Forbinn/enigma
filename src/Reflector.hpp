#pragma once

#include "Rotor.hpp"

namespace Enigma
{
class ENIGMA_EXPORT Reflector : public Rotor
{
public:
    enum class Standard
    {
        D_UKW,

        I_UKW_A,
        I_UKW_B,
        I_UKW_C,

        NORENIGMA_UKW,

        SONDER_UKW,

        M3_UKW_B,
        M3_UKW_C,

        M4_BETA,
        M4_GAMMA,
        M4_UKW_B,
        M4_UKW_C,

        G_UKW,

        G312_UKW,

        G260_UKW,

        K_UKW,

        SWISSK_UKW,

        KD_UKW,

        RAILWAY_UKW,

        T_UKW,

        Z_UKW
    };

public:
    Reflector();
    Reflector(const string & alphabet);
    Reflector(Standard r);

    bool isValid() const override;

public:
    bool rotate(bool = true) override;

public:
    static Enigma::string alphabetOfStandardReflector(Standard r);

public:
    std::size_t convertFrom(std::size_t idx) const override { return convertTo(idx); }
    std::size_t convert(std::size_t idx) const              { return convertTo(idx); }
};
} // !namespace Enigma
