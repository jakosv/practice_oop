#pragma once

#include "MatrixReduceOperation.h"
#include <vector>
#include <numeric>

template<typename T>
class MatrixRowSum : public MatrixReduceOperation<T> {
public:
    std::vector<T> calc(std::vector<std::vector<T>>& matrix) override;
};

template<typename T>
std::vector<T> MatrixRowSum<T>::calc(std::vector<std::vector<T>>& matrix) {
    std::vector<T> result(matrix.size());
    for (size_t i = 0; i < matrix.size(); i++) {
        result[i] = std::accumulate(matrix[i].begin(), matrix[i].end(), T()); 
    }
    return result;
}
