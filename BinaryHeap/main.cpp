#include "binaryHeap.h"

template<class T>
bool testHeapAdd(const std::vector<T>& initial, const T& value,
        const std::vector<T>& expected) 
{
    HeapOverArray<T> heap(initial);
    heap.addNode(value);
    auto v = heap.getVector();
    if (v.size() != expected.size()) {
        std::cerr << "size difference: expected " << expected.size() << 
            ", got " << v.size() << std::endl;
        return false; 
    }
    for (size_t i = 0; i < expected.size(); i++) {
        if (v[i] != expected[i]) {
            std::cerr << "diffecrence in " << i << ": expected " << 
                expected[i] << ", got " << v[i] << std::endl;
            return false;
        }
    }
    return true;
}

template<class T>
bool testHeapIterator(const std::vector<T>& initial,
        const std::vector<T>& expected)
{
    HeapOverArray<T> heap(initial);
    std::vector<T> v;
    for (auto it = heap.begin(); it; it++) {
        v.push_back(*it);
    }
    if (v.size() != expected.size()) {
        std::cerr << "size difference: expected " << expected.size() << 
            ", got " << v.size() << std::endl;
        return false; 
    }
    for (size_t i = 0; i < expected.size(); i++) {
        if (v[i] != expected[i]) {
            std::cerr << "diffecrence in " << i << ": expected " << 
                expected[i] << ", got " << v[i] << std::endl;
            return false;
        }
    }
    return true;
}

template<class T>
bool testHeapRemove(const std::vector<T>& initial, const T& value,
        const std::vector<T>& expected) 
{
    HeapOverArray<T> heap(initial);
    heap.removeNode(value);
    auto v = heap.getVector();
    if (v.size() != expected.size()) {
        std::cerr << "size difference: expected " << expected.size() << 
            ", got " << v.size() << std::endl;
        return false; 
    }
    for (size_t i = 0; i < expected.size(); i++) {
        if (v[i] != expected[i]) {
            std::cerr << "diffecrence in " << i << ": expected " << 
                expected[i] << ", got " << v[i] << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<int> initial = {7, 3, 4};
    std::vector<int> expected = {8, 7, 4, 3};
    testHeapAdd(initial, 8, expected);

    initial = {100, 70, 60, 25, 10, 40, 5, 8, 2, 9, 1, 3};
    expected = {8, 25, 2, 70, 9, 10, 1, 100, 3, 40, 60, 5};
    testHeapIterator(initial, expected);

    initial = {100, 70, 60, 25, 10, 40, 5, 8, 2, 9, 1, 3};
    expected = {100, 25, 60, 8, 10, 40, 5, 3, 2, 9, 1};
    testHeapRemove(initial, 70, expected);

    initial = {100, 70, 60, 25, 10, 40, 5, 8, 2, 9, 1, 30};
    expected = {100, 30, 60, 25, 10, 40, 5, 8, 2, 9, 1};
    testHeapRemove(initial, 70, expected);
    return 0;
}
