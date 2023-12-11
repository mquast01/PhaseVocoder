#pragma once

#include <type_traits>
#include <vector>
#include <iostream>

template<typename FloatType>
class CircularBuffer
{
    static_assert(std::is_floating_point<FloatType>::value == true,
                "template type must be a float or double"); 
    public:
        CircularBuffer(int max_size);
        FloatType readSample() const noexcept;
        FloatType writeSample(FloatType sample);
        FloatType *getData();

        int getMaxSize();
        bool isFull();
        int getIndex();

    private:
        std::vector<FloatType> buffer;
        int read = 0;
        int write = 0;
        int max_size;
        bool full = false;
};

#include "CircularBuffer.cpp"