#pragma once

#include <benchmark/benchmark.h>

#include "Rotors.hpp"

class BenchRotors : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State &) override;

    Enigma::Rotors r;
};
