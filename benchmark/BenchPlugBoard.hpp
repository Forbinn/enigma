#pragma once

#include <benchmark/benchmark.h>

#include "PlugBoard.hpp"

class BenchPlugBoard : public benchmark::Fixture
{
public:
    void SetUp(const benchmark::State &);

    Enigma::PlugBoard p;
};

