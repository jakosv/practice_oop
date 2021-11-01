#include <iostream>
#include <vector>

template<class T>
class HeapOverArray {
    std::vector<T> v;

public:
    HeapOverArray() {}
    HeapOverArray(const std::vector<T>& initv) : v(initv) {}

    const std::vector<T>& getVector() const { return v; }
    bool addNode(const T& o) {
        size_t pos = v.size();
        if (pos == 0) {
            v.push_back(o);
            return true;
        }
        size_t parent_pos = (pos - 1) / 2;
        v.push_back(o);
        while (pos != 0 && o > v[parent_pos]) {
            std::swap(v[pos], v[parent_pos]);
            pos = parent_pos;
            parent_pos = (pos - 1) / 2;
        }
        if (pos * 2 + 2 < v.size() && v[pos * 2 + 1] > v[pos * 2 + 2]) {
            std::swap(v[pos * 2 + 1], v[pos * 2 + 2]); 
        }
        return true;
    }

    T& getElement() {
        return v[0];
    }

    const T& getElement() const {
        return v[0];
    }

    bool removeNode(const T& o) {
        return true;
    }
};

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
        }
    }
    return true;
}

int main() {
    std::vector<int> initial = {7, 3, 4};
    std::vector<int> expected = {8, 4, 7, 3};
    testHeapAdd(initial, 8, expected);
    return 0;
}
