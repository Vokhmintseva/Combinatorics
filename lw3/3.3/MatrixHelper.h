#pragma once
#include <algorithm>
#include "SpanningTreesCountAlgorithm.h"

class MatrixHelper {
public:
    static void printMatrix—oefficients(const SpanningTreesCountAlgorithm::Matrix& m, std::ostream& output) {
        for (size_t i = 0; i < m.size(); ++i) {
            for (unsigned int j = 0; j < m[i].size(); j++) {
                if (m[i][j] == INT_MAX) {
                    output << "- ";
                }
                else {
                    output << m[i][j] << " ";
                }
            }
            output << "\n";
        }
    }
};