#pragma once

#include <vector>
#include "metrics.h"

std::vector<Metrics> grid_search_temporal_operator(
    const std::vector<uint8_t>& events,
    const std::vector<double>& alphas,
    const std::vector<double>& betas,
    const std::vector<double>& ks
);
