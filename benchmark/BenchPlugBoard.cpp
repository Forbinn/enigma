#include "BenchPlugBoard.hpp"

void BenchPlugBoard::SetUp(const benchmark::State &)
{
    p.addMapping('U', 'L');
    p.addMapping('X', 'V');
    p.addMapping('Z', 'H');
    p.addMapping('K', 'I');
    p.addMapping('J', 'M');
    p.addMapping('Q', 'C');
    p.addMapping('E', 'G');
    p.addMapping('T', 'S');
    p.addMapping('Y', 'W');
    p.addMapping('A', 'F');
}

BENCHMARK_F(BenchPlugBoard, benchMap)(benchmark::State & st)
{
    for (auto _ : st)
        benchmark::DoNotOptimize(p.map('A'));
    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()));
}

BENCHMARK_F(BenchPlugBoard, benchNotMapped)(benchmark::State & st)
{
    for (auto _ : st)
        benchmark::DoNotOptimize(p.map('B'));
    st.SetItemsProcessed(static_cast<int64_t>(st.iterations()));
}

BENCHMARK_F(BenchPlugBoard, benchAddMapping)(benchmark::State & st)
{
    auto cpy(p);
    for (auto _ : st)
        cpy.addMapping('B', 'A');
}

BENCHMARK_F(BenchPlugBoard, benchRemoveMapping)(benchmark::State & st)
{
    auto cpy(p);
    for (auto _ : st)
        cpy.removeMapping('A');
}

BENCHMARK_F(BenchPlugBoard, benchClear)(benchmark::State & st)
{
    auto cpy(p);
    for (auto _ : st)
        cpy.clear();
}

BENCHMARK_F(BenchPlugBoard, benchIsValid)(benchmark::State & st)
{
    for (auto _ : st)
        benchmark::DoNotOptimize(p.isValidForAlphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}
