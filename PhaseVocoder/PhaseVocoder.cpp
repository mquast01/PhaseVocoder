#include "PhaseVocoder.h"

using FloatType = float;

PhaseVocoder::PhaseVocoder(int _fftOrder, int _overlap) : 
    fftOrder(_fftOrder), 
    fftSize(1 << _fftOrder),
    overlap(_overlap),
    forwardFFT(std::make_unique<juce::dsp::FFT>(_fftOrder)), 
    analysisBuffer(fftSize),
    window(fftSize, 0),
    windowFunction(std::make_unique<juce::dsp::WindowingFunction<float>>(fftSize, JuceWindowTypes::hann))
    {};

void PhaseVocoder::process(float *buffer, int bufferSize) {
    
    DBG(" ");
    DBG("Processing samples #" << buffer[0] << " " << buffer[1] << " " << buffer[2] << "...");
    for(int i = 0; i < bufferSize; i++) {
        analysisBuffer.writeSample(buffer[i]);
        if(analysisBuffer.isFull()) {
            //apply window function
            windowFunction->multiplyWithWindowingTable(analysisBuffer.getData(), 1024);
            //FFT transform
            forwardFFT->performFrequencyOnlyForwardTransform(analysisBuffer.getData());
            //iFFT transform
            forwardFFT->performRealOnlyInverseTransform(analysisBuffer.getData());
        }
    }
}

