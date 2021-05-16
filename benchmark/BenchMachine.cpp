#include "BenchMachine.hpp"

void BenchMachine::SetUp(const benchmark::State &)
{
    m.rotors().appendRotor("JPGVOUMFYQBENHZRDKASXLICTW").setNotches({12, 25});
    m.rotors().appendRotor("VZBRGITYUPSDNHLXAWMJQOFECK").setNotches({25});
    m.rotors().appendRotor("ESOVPZJAYQUIRHXLNFTGKDCMWB").setNotches({9});
    m.rotors().setReflectorAlphabet("FVPJIAOYEDRZXWGCTKUQSBNMHL");

    m.plugboard().addMapping('U', 'L');
    m.plugboard().addMapping('X', 'V');
    m.plugboard().addMapping('Z', 'H');
    m.plugboard().addMapping('K', 'I');
    m.plugboard().addMapping('J', 'M');
    m.plugboard().addMapping('Q', 'C');
    m.plugboard().addMapping('E', 'G');
    m.plugboard().addMapping('T', 'S');
    m.plugboard().addMapping('Y', 'W');
    m.plugboard().addMapping('A', 'F');
}

BENCHMARK_DEFINE_F(BenchMachine, benchConvertSingleCharX)(benchmark::State & st)
{
    m.reset();
    for (auto _ : st)
        for (int64_t i = 0; i < st.range(); ++i)
            m.convert('A');

    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()) * st.range());
}
BENCHMARK_REGISTER_F(BenchMachine, benchConvertSingleCharX)->Range(10, 10 << 10);

BENCHMARK_F(BenchMachine, benchConvertHelloWorld)(benchmark::State & st)
{
    m.reset();
    for (auto _ : st)
        m.convert("Hello World!");

    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()));
    st.SetBytesProcessed(static_cast<int64_t>(st.iterations() * (sizeof("Hello World!") - 1)));
}

BENCHMARK_DEFINE_F(BenchMachine, benchConvertXA)(benchmark::State & st)
{
    const Enigma::string str(static_cast<std::size_t>(st.range(0)), 'A');

    for (auto _ : st)
        m.convert(str);

    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()));
    st.SetBytesProcessed(static_cast<int64_t>(st.iterations()) * st.range(0));
}
BENCHMARK_REGISTER_F(BenchMachine, benchConvertXA)->Range(10, 10 << 10);

BENCHMARK_DEFINE_F(BenchMachine, benchConvertXAX)(benchmark::State & st)
{
    const Enigma::string str(static_cast<std::size_t>(st.range(0)), 'A');

    for (auto _ : st)
        for (int64_t i = 0; i < st.range(1); ++i)
            m.convert(str);

    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()) * st.range(1));
    st.SetBytesProcessed(static_cast<int64_t>(st.iterations()) * st.range(0) * st.range(1));
}
BENCHMARK_REGISTER_F(BenchMachine, benchConvertXAX)->Ranges({{10, 512}, {10, 512}});

BENCHMARK_F(BenchMachine, benchClear)(benchmark::State & st)
{
    auto cpy(m);
    for (auto _ : st)
        cpy.clear();
}

BENCHMARK_F(BenchMachine, benchReset)(benchmark::State & st)
{
    for (auto _ : st)
        m.reset();
}

BENCHMARK_F(BenchMachine, benchIsValid)(benchmark::State & st)
{
    for (auto _ : st)
        benchmark::DoNotOptimize(m.isValid());
}
