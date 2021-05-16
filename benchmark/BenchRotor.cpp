#include "BenchRotor.hpp"

void BenchRotor::SetUp(const benchmark::State &)
{
    r.setAlphabet("EKMFLGDQVZNTOWYHXUSPAIBRCJ");
    r.setNotches({16});
}

BENCHMARK_F(BenchRotor, benchRotation)(benchmark::State & st)
{
    for (auto _ : st)
        r.rotate();
}

BENCHMARK_F(BenchRotor, benchRotationBack)(benchmark::State & st)
{
    for (auto _ : st)
        r.rotate(false);
}

BENCHMARK_F(BenchRotor, benchSetAlphabet)(benchmark::State & st)
{
    bool firstAlphabet = true;
    for (auto _ : st)
    {
        // Avoid any optimization like: if _internalAlphabet == newAlphabet then return
        r.setAlphabet(firstAlphabet ? "EKMFLGDQVZNTOWYHXUSPAIBRCJ" : "YRUHQSLDPXNGOKMIEBFZCWVJAT");
        firstAlphabet = !firstAlphabet;
    }
}

BENCHMARK_F(BenchRotor, benchIsValid)(benchmark::State & st)
{
    for (auto _ : st)
        benchmark::DoNotOptimize(r.isValid());
}

BENCHMARK_F(BenchRotor, benchReset)(benchmark::State & st)
{
    auto cpy(r);
    for (auto _ : st)
        cpy.reset();
}

BENCHMARK_F(BenchRotor, benchClear)(benchmark::State & st)
{
    auto cpy(r);
    for (auto _ : st)
        cpy.clear();
}

BENCHMARK_F(BenchRotor, benchIsInNotch)(benchmark::State & st)
{
    for (auto _ : st)
        benchmark::DoNotOptimize(r.isInNotchPosition());
}

BENCHMARK_DEFINE_F(BenchRotor, benchConvertToX)(benchmark::State & st)
{
    for (auto _ : st)
        for (int64_t i = 0; i < st.range(); ++i)
            benchmark::DoNotOptimize(r.convertTo(0));

    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()) * st.range());
}
BENCHMARK_REGISTER_F(BenchRotor, benchConvertToX)->Range(10, 10 << 10);

BENCHMARK_DEFINE_F(BenchRotor, benchConvertFromX)(benchmark::State & st)
{
    for (auto _ : st)
        for (int64_t i = 0; i < st.range(); ++i)
            benchmark::DoNotOptimize(r.convertFrom(0));

    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()) * st.range());
}
BENCHMARK_REGISTER_F(BenchRotor, benchConvertFromX)->Range(10, 10 << 10);
