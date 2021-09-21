#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Operation {
public:
    Operation() {}
    virtual ~Operation() {}
};

template<typename ResultT, typename ArgT>
class UnaryOperation : public Operation {
public:
    ResultT operator() (ArgT arg) const {
        return calc(arg);
    }
protected:
    virtual ResultT calc(ArgT arg) const = 0;
};

template<typename T>
class InverseOperation : public UnaryOperation<T, const T&> {
protected:
    T calc(const T& arg) const {
        return ~arg;
    }
};

template<typename ResultT, typename Arg1T, typename Arg2T>
class BinaryOperation : public Operation {
public:
    ResultT operator() (Arg1T arg1, Arg2T arg2) const {
        return calc(arg1, arg2);
    }

protected:
    virtual ResultT calc(Arg1T arg1, Arg2T arg2) const = 0;
};

template<typename T>
class SumOperation : public BinaryOperation<T, const T&, const T&> {
protected:
    T calc(const T& arg1, const T& arg2) const {
        return arg1 + arg2;
    }
};

template<typename T>
class VectorsAppendOperation : public BinaryOperation<std::vector<T>, 
                                const std::vector<T>&, const std::vector<T>&> 
{
protected:
    std::vector<T> calc(const std::vector<T>& arg1, 
                                        const std::vector<T>& arg2) const 
    {
        std::vector<T> newVector(arg1);
        for (size_t i = 0; i < arg2.size(); i++) {
            newVector.push_back(arg2[i]);
        }
        return newVector;
    }
};

template<typename T>
class VectorAppendOperation : public BinaryOperation<std::vector<T>, 
                                            const std::vector<T>&, const T&> 
{
protected:
    std::vector<T> calc(const std::vector<T>& arg1, const T& arg2) const 
    {
        std::vector<T> newVector(arg1);
        newVector.push_back(arg2);
        return newVector;
    }
};


template<typename ResultT, typename Arg1T, typename Arg2T, typename Arg3T>
class TernaryOperation : public Operation {
public:
    ResultT operator() (Arg1T arg1, Arg2T arg2, Arg3T arg3) const {
        return calc(arg1, arg2, arg3);
    }
protected:
    virtual ResultT calc(Arg1T arg1, Arg2T arg2, Arg3T arg3) const = 0;
};

template<typename T>
class IsInRangeOperation : public TernaryOperation<bool, const T&, 
                                                const T&, const T&> 
{
protected:
    bool calc(const T& from, const T& till, const T& elem) const {
        return (elem >= from && elem <= till);
    }
};

int main() {
    srand(time(NULL));
    int a = 5, b = 2;
    SumOperation<int> sum;
    std::cout << a << " + " << b << " = " << sum(a, b) << std::endl;

    std::vector<int> arr1 = {1, 2, 3};
    std::vector<int> arr2 = {4, 5};
    VectorsAppendOperation<int> vecsAppend;
    std::vector<int> result = vecsAppend(arr1, arr2);
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    VectorAppendOperation<int> vecAppend;
    result = vecAppend(result, 100);
    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    InverseOperation<int> inv;
    int c = 1;
    std::cout << inv(1) << std::endl;

    IsInRangeOperation<int> isInRange;
    if (isInRange(c, a, b)) {
        std::cout << "In range" << std::endl;
    }
    else {
        std::cout << "Not in range" << std::endl;
    }

    return 0;
}
