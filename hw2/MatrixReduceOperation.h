#pragma once

#include <vector>

template<typename T>
class MatrixReduceOperation {
public:
    virtual std::vector<T> calc(std::vector<std::vector<T>>& matrix) = 0;
};
