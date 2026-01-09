#include "temporal_operator.h"

std::vector<double> run_temporal_operator(
    const std::vector<uint8_t>& events,
    double alpha
) {
    std::vector<double> state(events.size(), 0.0);

    for (std::size_t t = 1; t < events.size(); ++t) {
        state[t] = alpha * state[t - 1] + events[t];
    }
    return state;
}
