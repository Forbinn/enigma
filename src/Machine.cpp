#include "Machine.hpp"

#include <random>
#include <functional>
#include <exception>

using ROS = Enigma::Rotor::Standard;
using RES = Enigma::Reflector::Standard;

const std::unordered_map<Enigma::Machine::Standard, Enigma::Machine::_MachineTemplate> Enigma::Machine::_machineTemplates = {
    { Standard::D, { { ROS::D_I, ROS::D_II, ROS::D_III, RES::D_UKW },
                     { ROS::D_I, ROS::D_II, ROS::D_III },
                       RES::D_UKW } },
    { Standard::I, { { ROS::I_I, ROS::I_II, ROS::I_III, ROS::I_IV, ROS::I_V, RES::I_UKW_A, RES::I_UKW_B, RES::I_UKW_C },
                     { ROS::I_I, ROS::I_II, ROS::I_III },
                       RES::I_UKW_A } },
    { Standard::Norenigma, { { ROS::NORENIGMA_I, ROS::NORENIGMA_II, ROS::NORENIGMA_III, ROS::NORENIGMA_IV, ROS::NORENIGMA_V, RES::NORENIGMA_UKW },
                             { ROS::NORENIGMA_I, ROS::NORENIGMA_II, ROS::NORENIGMA_III },
                               RES::NORENIGMA_UKW } },
    { Standard::Sonder, { { ROS::SONDER_I, ROS::SONDER_II, ROS::SONDER_III, RES::SONDER_UKW },
                          { ROS::SONDER_I, ROS::SONDER_II, ROS::SONDER_III },
                            RES::SONDER_UKW } },
    { Standard::M3, { { ROS::M3_I, ROS::M3_II, ROS::M3_III, ROS::M3_IV, ROS::M3_V, ROS::M3_VI, ROS::M3_VII, ROS::M3_VIII, RES::M3_UKW_B, RES::M3_UKW_C },
                      { ROS::M3_I, ROS::M3_II, ROS::M3_III },
                        RES::M3_UKW_B } },
    { Standard::M4, { { ROS::M4_I, ROS::M4_II, ROS::M4_III, ROS::M4_IV, ROS::M4_V, ROS::M4_VI, ROS::M4_VII, ROS::M4_VIII, RES::M4_BETA, RES::M4_GAMMA, RES::M4_UKW_B, RES::M4_UKW_C },
                      { ROS::M4_I, ROS::M4_II, ROS::M4_III, ROS::M4_IV },
                        RES::M4_BETA } },
    { Standard::G, { { ROS::G_I, ROS::G_II, ROS::G_III, RES::G_UKW },
                     { ROS::G_I, ROS::G_II, ROS::G_III },
                       RES::G_UKW } },
    { Standard::G312, { { ROS::G312_I, ROS::G312_II, ROS::G312_III, RES::G312_UKW },
                        { ROS::G312_I, ROS::G312_II, ROS::G312_III },
                          RES::G312_UKW } },
    { Standard::G260, { { ROS::G260_I, ROS::G260_II, ROS::G260_III, RES::G260_UKW },
                        { ROS::G260_I, ROS::G260_II, ROS::G260_III },
                          RES::G260_UKW } },
    { Standard::K, { { ROS::K_I, ROS::K_II, ROS::K_III, RES::K_UKW },
                     { ROS::K_I, ROS::K_II, ROS::K_III },
                       RES::K_UKW } },
    { Standard::SwissK, { { ROS::SWISSK_I, ROS::SWISSK_II, ROS::SWISSK_III, RES::SWISSK_UKW },
                          { ROS::SWISSK_I, ROS::SWISSK_II, ROS::SWISSK_III },
                            RES::SWISSK_UKW } },
    { Standard::KD, { { ROS::KD_I, ROS::KD_II, ROS::KD_III, RES::KD_UKW },
                      { ROS::KD_I, ROS::KD_II, ROS::KD_III },
                        RES::KD_UKW } },
    { Standard::Railway, { { ROS::RAILWAY_I, ROS::RAILWAY_II, ROS::RAILWAY_III, RES::RAILWAY_UKW },
                           { ROS::RAILWAY_I, ROS::RAILWAY_II, ROS::RAILWAY_III },
                             RES::RAILWAY_UKW } },
    { Standard::T, { { ROS::T_I, ROS::T_II, ROS::T_III, ROS::T_IV, ROS::T_V, ROS::T_VI, ROS::T_VII, ROS::T_VIII, RES::T_UKW },
                     { ROS::T_I, ROS::T_II, ROS::T_III },
                       RES::T_UKW } },
    { Standard::Z, { { ROS::Z_I, ROS::Z_II, ROS::Z_III, RES::Z_UKW },
                     { ROS::Z_I, ROS::Z_II, ROS::Z_III },
                       RES::Z_UKW } }
};

namespace
{
// https://en.cppreference.com/w/cpp/utility/variant/visit
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
} // !namespace

bool Enigma::Machine::isValid() const
{
    if (!_rotors.isValid())
        return false;

    return _plugboard.isValidForAlphabet(_rotors.inputAlphabet());
}

Enigma::value_type Enigma::Machine::convert(value_type v)
{
    v = _plugboard.map(v);
    v = _rotors.convert(v);
    v = _plugboard.map(v);

    return v;
}

Enigma::string Enigma::Machine::convert(string_view s)
{
    string output;
    output.reserve(s.size());
    for (const auto & v : s)
        output.push_back(convert(v));
    return output;
}

void Enigma::Machine::clear()
{
    _rotors.clear();
    _plugboard.clear();
}

void Enigma::Machine::reset()
{
    _rotors.reset();
}

Enigma::Machine Enigma::Machine::build(Standard machine, ORotorType r1, ORotorType r2, ORotorType r3, ORotorType r4, ORotorType r5)
{

    Machine m;
    std::vector<ROS> alreadySetRotors;

    const overloaded visitor {
        [&m, &alreadySetRotors](ROS r)
        {
            if (std::find(alreadySetRotors.begin(), alreadySetRotors.end(), r) != alreadySetRotors.end())
                throw std::invalid_argument("You cannot set the same rotor more than once for the same machine");
            m.rotors().appendRotor(r);
            alreadySetRotors.emplace_back(r);
        },
        [&m](RES r)
        {
            if (m.rotors().reflector().isValid())
                throw std::invalid_argument("You cannot set two reflector for the same machine");
            m.rotors().setReflector(r);
        }
    };

    const auto & machineTemplate = _machineTemplates.at(machine);
    const auto allR              = { r1, r2, r3, r4, r5 };
    int i = 0;
    for (const auto & r : allR)
    {
        ++i;
        if (!r.has_value())
            continue;

        const auto & allowedValues = machineTemplate.allowedValues;
        if (std::find(allowedValues.begin(), allowedValues.end(), r.value()) == allowedValues.end())
            throw std::invalid_argument("r" + std::to_string(i) + " argument contains an invalid value for this machine type");

        // Use visitor pattern to easily set either a reflector or a rotor
        // Will throw aan exception if an invalid value is provided
        std::visit(visitor, r.value());
    }

    // If a reflector hasn't been set by the user then use the default one
    if (!m.rotors().reflector().isValid())
        m.rotors().setReflector(machineTemplate.defaultReflector);

    // If no rotor has been provided then set the default ones
    if (m.rotors().rotorCount() == 0)
    {
        for (const auto & r : machineTemplate.defaultRotors)
            m.rotors().appendRotor(r);
    }
    else if (m.rotors().rotorCount() != machineTemplate.defaultRotors.size())
        throw std::invalid_argument("This machine model have 3 rotors. Precise either all or none of them");

    return m;
}

Enigma::Machine Enigma::Machine::buildRandomMachine(string_view alphabet,
                                                    std::size_t rotorCount,
                                                    std::size_t plugboardSwap)
{
    // Sanity check
    if (alphabet.empty() || rotorCount == 0)
        return {};
    else if (plugboardSwap > 0 && alphabet.size() % 2 != 0)
        return {};

    using RandomEngine       = std::mt19937;
    using RandomDevice       = std::random_device;
    using SeedData           = std::array<std::seed_seq::result_type, RandomEngine::state_size>;
    using RandomDistribution = std::uniform_int_distribution<string::size_type>;
    using ResultType         = RandomDistribution::result_type;
    using Params             = RandomDistribution::param_type;

    // Initialize a static random engine
    static RandomEngine randomEngine = []
    {
        RandomEngine engine;
        RandomDevice device;
        SeedData     seedData;

        std::generate(seedData.begin(), seedData.end(), std::ref(device));
        std::seed_seq seeds(seedData.begin(), seedData.end());

        engine.seed(seeds);
        return engine;
    }();

    // Now create the machine it-self
    const auto generateRandomAlphabet = [&alphabet]
    {
        string outAlphabet(alphabet);
        std::shuffle(outAlphabet.begin(), outAlphabet.end(), randomEngine);
        return outAlphabet;
    };

    Machine machine;

    // Create all rotors
    for (std::size_t i = 0; i < rotorCount; ++i)
        machine.rotors().appendRotor(generateRandomAlphabet());

    // Setup a random reflector
    while (!machine.rotors().reflector().isValid())
        machine.rotors().setReflectorAlphabet(generateRandomAlphabet());

    if (plugboardSwap > 0)
    {
        plugboardSwap = std::min(plugboardSwap, alphabet.size() / 2);

        string remainingAlphabet(alphabet);

        RandomDistribution dis;

        // Create a function to easily generate two random (but different) indexes
        const auto randomIndexes = [&dis, &remainingAlphabet]() -> std::pair<ResultType, ResultType>
        {
            // Use a shortcut instead of generating random number. The result will be the same
            if (remainingAlphabet.size() == 2)
                return { 0, 1 };

            const auto inputIdx  = dis(randomEngine, Params{ 0, remainingAlphabet.size() - 1 });
            ResultType outputIdx = 0;

            do
            { outputIdx = dis(randomEngine, Params{ 0, remainingAlphabet.size() - 1 }); }
            while (inputIdx == outputIdx);

            return { inputIdx, outputIdx };
        };

        for (std::size_t i = 0; i < plugboardSwap; ++i)
        {
            const auto [inputIdx, outputIdx] = randomIndexes();
            const auto firstIdx              = std::min(inputIdx, outputIdx);
            const auto lastIdx               = std::max(inputIdx, outputIdx);

            machine.plugboard().addMapping(remainingAlphabet.at(firstIdx),
                                           remainingAlphabet.at(lastIdx));

            // Remove the character that have already been used
            remainingAlphabet.erase(firstIdx, 1);
            remainingAlphabet.erase(lastIdx - 1, 1);
        }
    }

    return machine;
}
