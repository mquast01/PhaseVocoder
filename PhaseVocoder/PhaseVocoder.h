#pragma once

#include <algorithm>
#include <iostream>
#include <juce_dsp/juce_dsp.h>
#include "CircularBuffer.h"

class PhaseVocoder
{
    public: 
        using JuceWindow = typename juce::dsp::WindowingFunction<float>;
        using JuceWindowTypes = typename juce::dsp::WindowingFunction<float>::WindowingMethod;

        PhaseVocoder(int _fftOrder, int _overlap = 2);
        void process(float *buffer, int bufferSize);
        void initializeWindow(JuceWindowTypes window);
        
    private:
        int fftOrder;
        int fftSize;
        int overlap;
        bool nextFFTBlockReady = false;

        std::unique_ptr<juce::dsp::FFT> forwardFFT;  
        CircularBuffer<float> analysisBuffer;
        std::vector<float> window;
        std::vector<float> frequencySpectrum;

        std::unique_ptr<juce::dsp::WindowingFunction< float >> windowFunction;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhaseVocoder)
};


