#pragma once

#include "enigma_global.hpp"

#include <vector>

// https://www.cryptomuseum.com/crypto/enigma/wiring.htm
// On this website the notch field can be ignored. It is the turnover field that's important

namespace Enigma
{
// TODO: Add ring concept (https://en.wikipedia.org/wiki/Enigma_rotor_details#Ring_setting)
class ENIGMA_EXPORT Rotor
{
public:
    enum class Standard
    {
        D_I,
        D_II,
        D_III,

        I_I,
        I_II,
        I_III,
        I_IV,
        I_V,

        NORENIGMA_I,
        NORENIGMA_II,
        NORENIGMA_III,
        NORENIGMA_IV,
        NORENIGMA_V,

        SONDER_I,
        SONDER_II,
        SONDER_III,

        M3_I,
        M3_II,
        M3_III,
        M3_IV,
        M3_V,
        M3_VI,
        M3_VII,
        M3_VIII,

        M4_I,
        M4_II,
        M4_III,
        M4_IV,
        M4_V,
        M4_VI,
        M4_VII,
        M4_VIII,

        G_I,
        G_II,
        G_III,

        G312_I,
        G312_II,
        G312_III,

        G260_I,
        G260_II,
        G260_III,

        K_I,
        K_II,
        K_III,

        SWISSK_I,
        SWISSK_II,
        SWISSK_III,

        KD_I,
        KD_II,
        KD_III,

        RAILWAY_I,
        RAILWAY_II,
        RAILWAY_III,

        T_I,
        T_II,
        T_III,
        T_IV,
        T_V,
        T_VI,
        T_VII,
        T_VIII,

        Z_I,
        Z_II,
        Z_III
    };

public:
    using Wires = std::vector<std::pair<int, int>>;

public:
    Rotor() = default;
    Rotor(string_view alphabet, string_view notches = {});
    Rotor(Standard r);
    virtual ~Rotor() = default;

    virtual bool isValid() const { return !_wires.empty(); }

public:
    void setAlphabet(string_view alphabet, string_view notches = {});

    void setNotches(const std::vector<std::size_t> & notches);
    void addNotch(std::size_t idx);
    void removeNotch(std::size_t idx);
    std::size_t notchCount() const { return _notches.size(); }
    const std::vector<std::size_t> & notches() const { return _notches; }

    bool isInNotchPosition() const;

public:
    void setRotation(std::size_t rotation);
    std::size_t rotation() const { return _rotation; }
    virtual bool rotate(bool forward = true);

    virtual std::size_t convertTo(std::size_t idx) const;
    virtual std::size_t convertFrom(std::size_t idx) const;

public:
    void clear();
    void reset();

public:
    static string_view alphabetOfStandardRotor(Standard r);
    static string_view notchesOfStandardRotor(Standard r);

protected:
    Rotor(bool allowStraightWire);

private:
    bool _hasCrossedANotch(bool forward) const;

protected:
    Wires _wires;

private:
    std::vector<std::size_t> _notches;
    std::size_t              _rotation = 0;

private:
    // Cannot be set to const because the class will become unusable in a std::vector
    // It will loose the MoveAssignable requirement
    bool _allowStraightWire = true;
};
} // !namespace Enigma
