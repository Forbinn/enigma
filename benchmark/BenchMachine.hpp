#pragma once

#include <benchmark/benchmark.h>

#include "Machine.hpp"

class BenchMachine : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State &) override;

    Enigma::Machine m;
};

