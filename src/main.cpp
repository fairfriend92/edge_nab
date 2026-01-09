#include <iostream>
#include "nab_loader.h"
#include "event_encoder.h"
#include "temporal_operator.h"
#include "benchmark.h"
#include "csv_writer.h"

constexpr int N_RUNS = 1000;

int main() {
    Timer timer;

    timer.tic();
    auto ts = load_nab_csv("../data/ambient_temperature_system_failure.csv");
    double t_load = timer.toc_ms();

    timer.tic();
    auto events = encode_events(ts.values, 1.0);
    double t_encode = timer.toc_ms();

    timer.tic();
    for (int i = 0; i < N_RUNS; ++i) {
        run_temporal_operator(events, 0.95);
    }
    double t_op = timer.toc_ms() / N_RUNS;

    std::cout << "Load:   " << t_load   << " ms\n";
    std::cout << "Encode: " << t_encode << " ms\n";
    std::cout << "Op:     " << t_op     << " ms\n";
    std::cout << "Total samples: " << ts.values.size() << "\n";

    auto scores = run_temporal_operator(events, 0.95);
    write_csv("../outputs/scores.csv", scores);    

    return 0;
}
