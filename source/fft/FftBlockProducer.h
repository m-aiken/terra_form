#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"

class FftBlockProducer
{
public:
    FftBlockProducer();

    void               pushSample(const float sample);
    [[nodiscard]] bool nextBlockReady();
    void               getNextBlock(terra_form::fft::FftDataBlock& buffer_to_fill);

private:
    void performFft(terra_form::fft::FftDataBlock& fft_data) const;

    juce::dsp::FFT                        fft_;
    juce::dsp::WindowingFunction< float > windowing_function_;

    std::array< float, terra_form::fft::FFT_SIZE > fifo_;
    size_t                                         fifo_index_;
    terra_form::fft::FftDataBlock                  fft_data_;
    juce::CriticalSection                          fft_data_critical_section_;
    juce::Atomic< bool >                           next_block_ready_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FftBlockProducer)
};
