#include "grid_search.h"
#include "temporal_operator.h"
#include "metrics.h"
#include <algorithm>

std::vector<Metrics> grid_search_temporal_operator(
    const std::vector<uint8_t>& events,
    const std::vector<double>& alphas,
    const std::vector<double>& betas,
    const std::vector<double>& ks
) {
    std::vector<Metrics> results;
    const std::size_t T = events.size();

    for (double alpha : alphas) {
        for (double beta : betas) {
            for (double k : ks) {

                auto out = run_temporal_operator(
                    events, alpha, beta, 0.0, k
                );

                auto m = evaluate(out, {alpha, beta, 0.0, k});
                results.push_back(m);
            }
        }
    }

    // Filter results
    results.erase(
        std::remove_if(results.begin(), results.end(),
            [T](const Metrics& m) {
                return m.anomaly_count == 0 ||
                       m.anomaly_count > 0.2 * T;
            }),
        results.end()
    );

    // Order results
    std::sort(results.begin(), results.end(),
        [](const Metrics& a, const Metrics& b) {
            return a.ratio > b.ratio;
        });

    return results;
}
