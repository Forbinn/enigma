#pragma once

#include <benchmark/benchmark.h>

#include "Rotor.hpp"

class BenchRotor : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State & s) override;

    Enigma::Rotor r;
};
