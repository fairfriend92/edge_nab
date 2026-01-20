#pragma once
#include <cstddef>
#include "temporal_operator.h"

struct Params {
    double alpha;
    double beta;
    double gamma;
    double k;
};

struct Metrics {
    Params params;

    std::size_t anomaly_count;
    double mean_score;
    double mean_score_anomaly;
    double ratio; // mean_score_anomaly / mean_score
};

Metrics evaluate(
    const TemporalOutput& out,
    const Params& params
);