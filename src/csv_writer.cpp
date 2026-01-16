#include "csv_writer.h"
#include <fstream>
#include <cstddef>

void write_csv(
    const std::string& path,
    const std::vector<double>& state,
    const std::vector<double>& baseline,
    const std::vector<double>& score,
    const std::vector<uint8_t>& anomaly
) {
    std::ofstream file(path);
    file << "t,state,baseline,score,anomaly\n";

    const std::size_t T = state.size();
    for (std::size_t t = 0; t < T; ++t) {
        file << t << ","
         << state[t] << ","
         << baseline[t] << ","
         << score[t] << ","
         << int(anomaly[t]) << "\n";
    }
}
