#include "metrics.h"

Metrics evaluate(
    const TemporalOutput& out,
    const Params& params
) {
    Metrics m{};
    m.params = params;

    double sum_score = 0.0;
    double sum_anom_score = 0.0;
    std::size_t anom_steps = 0;

    const std::size_t T = out.score.size();

    for (std::size_t t = 0; t < T; ++t) {
        sum_score += out.score[t];

        if (out.anomaly[t]) {
            m.anomaly_count++;
            sum_anom_score += out.score[t];
            anom_steps++;
        }
    }

    m.mean_score = sum_score / T;
    m.mean_score_anomaly =
        (anom_steps > 0) ? sum_anom_score / anom_steps : 0.0;

    m.ratio =
        (m.mean_score > 0.0)
            ? m.mean_score_anomaly / m.mean_score
            : 0.0;

    return m;
}
