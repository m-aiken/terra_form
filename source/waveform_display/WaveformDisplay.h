#pragma once

#include <JuceHeader.h>

#include "GlobalConstants.h"
#include "TerraFormProcessor.h"

class WaveformDisplay final
    : public juce::Component
    , public juce::Timer
{
public:
    explicit WaveformDisplay(TerraFormProcessor& p);
    ~WaveformDisplay() override;

    void paint(juce::Graphics& g) override;
    void timerCallback() override;

private:
    double       getBinWidth() const;
    juce::Path   getWaveformPath(const TerraForm::FFT::FftDataBlock& fft_data, const int path_index) const;
    static float getYCoordinate(const float& sample, const int& dest_height);

    TerraFormProcessor&           processor_ref_;
    TerraForm::FFT::PathDataArray waveform_data_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
