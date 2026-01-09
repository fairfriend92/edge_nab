#pragma once
#include <vector>
#include <cstdint>

std::vector<uint8_t> encode_events(
    const std::vector<double>& x,
    double threshold
);
