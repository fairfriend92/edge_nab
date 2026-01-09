#include "csv_writer.h"
#include <fstream>

void write_csv(
    const std::string& path,
    const std::vector<double>& scores
) {
    std::ofstream file(path);
    file << "t,score\n";
    for (std::size_t i = 0; i < scores.size(); ++i) {
        file << i << "," << scores[i] << "\n";
    }
}
