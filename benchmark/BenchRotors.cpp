#include "BenchRotors.hpp"

#include <chrono>

void BenchRotors::SetUp(const benchmark::State &)
{
    r.appendRotor("EKMFLGDQVZNTOWYHXUSPAIBRCJ").setNotches({16});
    r.appendRotor("AJDKSIRUXBLHWTMCQGZNPYFVOE").setNotches({4});
    r.appendRotor("BDFHJLCPRTXVZNYEIWGAKMUSQO").setNotches({21});
    r.setReflectorAlphabet("YRUHQSLDPXNGOKMIEBFZCWVJAT");
}

BENCHMARK_DEFINE_F(BenchRotors, benchConvertX)(benchmark::State & st)
{
    for (auto _ : st)
        for (int64_t i = 0; i < st.range(); ++i)
            r.convert('A');

    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()) * st.range());
}
BENCHMARK_REGISTER_F(BenchRotors, benchConvertX)->Range(10, 10 << 10);

BENCHMARK_DEFINE_F(BenchRotors, benchRemoveRotor)(benchmark::State & st)
{
    for (auto _ : st)
    {
        auto cpy(r);

        const auto start = std::chrono::high_resolution_clock::now();
        cpy.removeRotor(1);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        st.SetIterationTime(elapsed_seconds.count());
    }
}
BENCHMARK_REGISTER_F(BenchRotors, benchRemoveRotor)->UseManualTime();

BENCHMARK_F(BenchRotors, benchReset)(benchmark::State & st)
{
    for (auto _ : st)
        r.reset();
}

BENCHMARK_F(BenchRotors, benchClear)(benchmark::State & st)
{
    auto cpy(r);
    for (auto _ : st)
        cpy.clear();
}

BENCHMARK_F(BenchRotors, benchAppendRotor)(benchmark::State & st)
{
    Enigma::Rotors rs;
    for (auto _ : st)
        rs.appendRotor("ESOVPZJAYQUIRHXLNFTGKDCMWB");
}

BENCHMARK_F(BenchRotors, benchPrependRotor)(benchmark::State & st)
{
    Enigma::Rotors rs;
    for (auto _ : st)
        rs.prependRotor("ESOVPZJAYQUIRHXLNFTGKDCMWB");
}
