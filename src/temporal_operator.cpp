#include "temporal_operator.h"

TemporalOutput run_temporal_operator(
    const std::vector<uint8_t>& events,
    double alpha,
    double beta,
    double gamma,
    double k
) {
    const std::size_t T = events.size();

    TemporalOutput out;
    out.state.resize(T, 0.0);
    out.baseline.resize(T, 0.0);
    out.score.resize(T, 0.0);
    out.anomaly.resize(T, 0);

    for (std::size_t t = 1; t < T; ++t) {
        out.state[t] = alpha * out.state[t - 1] + events[t];

        if (events[t] == 0)
            out.state[t] *= (1.0 - gamma);

        out.baseline[t] =
            beta * out.baseline[t - 1] +
            (1.0 - beta) * out.state[t];

        // ReLU
        double raw = out.state[t] - out.baseline[t];
        out.score[t] = (raw > 0.0) ? raw : 0.0;

        // Threshold
        out.anomaly[t] = (out.score[t] > k * out.baseline[t]) ? 1 : 0;
    }

    return out;
}