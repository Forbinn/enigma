#include <benchmark/benchmark.h>

#if 0
#include "Machine.hpp"

int main()
{
    Enigma::Rotors r;
    r.appendRotor("EKMFLGDQVZNTOWYHXUSPAIBRCJ");
    r.appendRotor("AJDKSIRUXBLHWTMCQGZNPYFVOE");
    r.appendRotor("BDFHJLCPRTXVZNYEIWGAKMUSQO");
    r.setReflectorAlphabet("YRUHQSLDPXNGOKMIEBFZCWVJAT");

    for (int i = 0; i < 1'000'000; ++i)
        benchmark::DoNotOptimize(r.convert('A'));
}
#else
BENCHMARK_MAIN();
#endif
