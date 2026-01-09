#include "nab_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

TimeSeries load_nab_csv(const std::string& path) {
    TimeSeries ts;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open NAB file");
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string ts_str, value_str;
        std::getline(ss, ts_str, ',');
        std::getline(ss, value_str, ',');

        ts.values.push_back(std::stod(value_str));
    }

    return ts;
}
