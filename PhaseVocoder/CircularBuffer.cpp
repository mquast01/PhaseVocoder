#include "CircularBuffer.h"

template <typename FloatType>
CircularBuffer<FloatType>::CircularBuffer(int _max_size)
    : buffer(_max_size, 0), max_size(_max_size), full(false) {}

template <typename FloatType>
FloatType CircularBuffer<FloatType>::readSample() const noexcept { return buffer[read]; }

template <typename FloatType>
FloatType CircularBuffer<FloatType>::writeSample(FloatType sample) {
    auto discarded = buffer[write];
    buffer[write] = sample;
    
    if( write >= (getMaxSize() - 1)) {
        write = 0;
    } else {
        ++write;
    }
    
    if( read >= (getMaxSize() - 1)) {
        read = 0;

    } else {
        ++read;
    }

    return discarded;
}

template <typename FloatType>
FloatType *CircularBuffer<FloatType>::getData() {
    return buffer.data();
}

template <typename FloatType>
int CircularBuffer<FloatType>::getMaxSize() {
    return max_size;
}

template <typename FloatType>
bool CircularBuffer<FloatType>::isFull() {
    return write == 0;
}

template <typename FloatType>
int CircularBuffer<FloatType>::getIndex() {
    return write;
}