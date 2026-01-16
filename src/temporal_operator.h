#pragma once
#include <vector>
#include <cstdint>
#include <cstddef>

struct TemporalOutput {
    std::vector<double> state;
    std::vector<double> baseline;
    std::vector<double> score;
    std::vector<uint8_t> anomaly;
};

TemporalOutput run_temporal_operator(
    const std::vector<uint8_t>& events,
    double alpha,
    double beta,
    double gamma,
    double k
);
