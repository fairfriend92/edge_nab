#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "nab_loader.h"
#include "event_encoder.h"
#include "temporal_operator.h"
#include "benchmark.h"
#include "csv_writer.h"
#include "grid_search.h"
#include "metrics.h"

constexpr int N_RUNS = 1000;

int main() {
    Timer timer;

    // Load data
    timer.tic();
    auto ts = load_nab_csv("../data/ambient_temperature_system_failure.csv");
    double t_load = timer.toc_ms();

    // Encode events
    timer.tic();
    auto events = encode_events(ts.values, 1.0);  
    size_t T = events.size();  
    double t_encode = timer.toc_ms();    
    float event_rate =
        static_cast<float>(
            std::accumulate(events.begin(), events.end(), 0)
        ) / static_cast<float>(T);
    std::cout << "Event rate: " << event_rate << "%\n";

    // Do a grid search of the temporal operator parameters
    std::vector<double> alphas = {0.90, 0.93, 0.95, 0.97};
    std::vector<double> betas  = {0.990, 0.995, 0.999};
    std::vector<double> ks     = {2.0, 2.5, 3.0};
    auto results = grid_search_temporal_operator(
      events, alphas, betas, ks
    );

    // Save gridsearch scores 
    for (std::size_t i = 0; i < std::min(results.size(), size_t(5)); ++i) {
        const auto& m = results[i];

        auto out = run_temporal_operator(
            events,
            m.params.alpha,
            m.params.beta,
            m.params.gamma,
            m.params.k
        );

        std::ostringstream oss;
        oss << "../outputs/top_" << i
            << "_a" << std::fixed << std::setprecision(2) << m.params.alpha
            << "_b" << std::setprecision(3) << m.params.beta
            << "_k" << std::setprecision(1) << m.params.k
            << ".csv";

        write_csv(
            oss.str(),
            out.state,
            out.baseline,
            out.score,
            out.anomaly
        );
    }

    // Benchmark 
    const auto& p = results[0].params;
    timer.tic();
    for (int i = 0; i < N_RUNS; ++i) {
        run_temporal_operator(
          events, p.alpha, p.beta, p.gamma, p.k);
    }
    double t_op = timer.toc_ms() / N_RUNS;

    std::cout << "Load:   " << t_load   << " ms\n";
    std::cout << "Encode: " << t_encode << " ms\n";
    std::cout << "Op:     " << t_op     << " ms\n";
    std::cout << "Total samples: " << ts.values.size() << "\n";
    return 0;
}
