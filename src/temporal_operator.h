#pragma once
#include <vector>
#include <cstdint>

std::vector<double> run_temporal_operator(
    const std::vector<uint8_t>& events,
    double alpha
);
