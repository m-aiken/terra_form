#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class FftBlockProducer
{
public:
    FftBlockProducer();

    void                          pushSample(const float sample);
    bool                          nextBlockReady() const;
    TerraForm::FFT::FftDataBlock& getNextBlock();

private:
    void performFft(TerraForm::FFT::FftDataBlock& fft_data) const;

    juce::dsp::FFT                        fft_;
    juce::dsp::WindowingFunction< float > windowing_function_;

    std::array< float, TerraForm::FFT::FFT_SIZE > fifo_;
    size_t                                        fifo_index_;
    TerraForm::FFT::FftDataBlock                  fft_data_;
    bool                                          next_block_ready_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FftBlockProducer)
};
