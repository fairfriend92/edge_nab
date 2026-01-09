#include "event_encoder.h"
#include <cmath>

std::vector<uint8_t> encode_events(
    const std::vector<double>& x,
    double threshold
) {
    std::vector<uint8_t> events(x.size(), 0);

    for (size_t i = 1; i < x.size(); ++i) {
        double delta = std::abs(x[i] - x[i - 1]);
        events[i] = (delta > threshold) ? 1 : 0;
    }
    return events;
}
