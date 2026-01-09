#pragma once
#include <vector>
#include <string>

struct TimeSeries {
    std::vector<double> values;
};

TimeSeries load_nab_csv(const std::string& path);