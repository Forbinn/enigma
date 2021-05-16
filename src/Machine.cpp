#include "Machine.hpp"

#include <random>
#include <functional>

bool Enigma::Machine::isValid() const
{
    if (!_rotors.isValid())
        return false;

    return true;
}

Enigma::value_type Enigma::Machine::convert(Enigma::value_type v)
{
    v = _plugboard.map(v);
    v = _rotors.convert(v);
    v = _plugboard.map(v);

    return v;
}

Enigma::string Enigma::Machine::convert(const Enigma::string & s)
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

Enigma::Machine Enigma::Machine::buildRandomMachine(const string & alphabet,
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

    // Then we just have to crete the other ones
    for (std::size_t i = 0; i < rotorCount; ++i)
        machine.rotors().appendRotor(generateRandomAlphabet());

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
