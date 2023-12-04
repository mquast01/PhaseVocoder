#include "PhaseVocoder.h"

using FloatType = float;

PhaseVocoder::PhaseVocoder(int _fftOrder, int _overlap) : 
    fftOrder(_fftOrder), 
    fftSize(1 << _fftOrder),
    overlap(_overlap),
    forwardFFT(std::make_unique<juce::dsp::FFT>(_fftOrder)), 
    analysisBuffer(fftSize),
    frequencySpectrum(fftSize * 2),
    window(fftSize, 0),
    windowFunction(std::make_unique<juce::dsp::WindowingFunction<float>>(fftSize, JuceWindowTypes::hann))
    {};

void PhaseVocoder::process(float *buffer, int bufferSize) {
    
    DBG(" ");
    DBG("Processing samples #" << buffer[0] << " " << buffer[1] << " " << buffer[2] << "...");
    for(int i = 0, j = 0; i < bufferSize; i++) {
        analysisBuffer.writeSample(buffer[i]);
        float *data = analysisBuffer.getData();
        if(analysisBuffer.isFull()) {
            //apply window function
            windowFunction->multiplyWithWindowingTable(data, 1024);
            //FFT transform
            std::fill(frequencySpectrum.begin(), frequencySpectrum.end(), 0);
            std::copy(data, data + fftSize, frequencySpectrum.data());
            forwardFFT->performFrequencyOnlyForwardTransform(frequencySpectrum.data());
            //iFFT transform
            forwardFFT->performRealOnlyInverseTransform(frequencySpectrum.data());
            j = 0;
        } else j++;
        //std::copy(data, data, buffer);
    }
}

