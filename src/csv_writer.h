#pragma once
#include <vector>
#include <string>

void write_csv(
    const std::string& path,
    const std::vector<double>& state,
    const std::vector<double>& baseline,
    const std::vector<double>& score,
    const std::vector<uint8_t>& anomaly
);
