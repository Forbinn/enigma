#pragma once

#include "enigma_global.hpp"
#include "Rotors.hpp"
#include "PlugBoard.hpp"

#include <variant>
#include <optional>

namespace Enigma
{
class ENIGMA_EXPORT Machine
{
    // TODO: Fix README file formatting
public:
    using RotorType  = std::variant<Rotor::Standard, Reflector::Standard>;
    using ORotorType = std::optional<RotorType>;

public:
    enum class Standard
    {
        D,         //! Main commercial machine
        I,         //! Main military machine with 3 rotors (You can choose between 5 rotors and 3 reflectors)
        Norenigma, //! Norway variant of the model I (You can choose between 5 rotors)
        Sonder,    //! Special variant of the model I
        M3,        //! Standard 3 rotors machine (You can choose between 8 rotors and 2 reflectors)
        M4,        //! Standard 4 rotors machine (You can choose between 8 rotors and 4 reflectors)
        G,         //! Variant of the model D
        G312,      //! Variant of the model G
        G260,      //! Variant of the model G
        K,         //! Same as the model D
        SwissK,    //! Variant of the model K
        KD,        //! Commercial version of the model K
        Railway,   //! Railway version of the model K
        T,         //! Japanese version of the model K (You can choose between 8 rotors)
        Z          //! Numeric version of the mochine
    };

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
    // Max 4 rotor and 1 reflector
    static Machine build(Standard machine, ORotorType r1 = {}, ORotorType r2 = {}, ORotorType r3 = {}, ORotorType r4 = {}, ORotorType r5 = {});

    static Machine buildRandomMachine(const string & alphabet = "abcdefghijklmnopqrstuvwxyz",
                                      std::size_t rotorCount = 3,
                                      std::size_t plugboardSwap = 10);

private:
    struct _MachineTemplate
    {
        _MachineTemplate(std::vector<RotorType> && a,
                         std::vector<Rotor::Standard> && dro,
                         Reflector::Standard dre)
            : allowedValues    { std::move(a) }
            , defaultRotors    { std::move(dro) }
            , defaultReflector { dre }
        {}

        std::vector<RotorType>       allowedValues;
        std::vector<Rotor::Standard> defaultRotors;
        Reflector::Standard          defaultReflector;
    };

private:
    static const std::unordered_map<Standard, _MachineTemplate> _machineTemplates;

private:
    Rotors    _rotors;
    PlugBoard _plugboard;
};
} // !namespace Enigma

