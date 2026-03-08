#pragma once

#include <JuceHeader.h>

#include "ColourPicker.h"
#include "GlobalConstants.h"
#include "TerraFormProcessor.h"

class WaveformDisplay final
    : public juce::Component
    , public juce::Timer
    , public juce::ChangeListener
{
public:
    explicit WaveformDisplay(TerraFormProcessor& p, ColourPicker& colour_picker);
    ~WaveformDisplay() override;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    juce::Path getWaveformPath(const TerraForm::FFT::FftDataBlock& fft_data, const size_t path_index) const;

    TerraFormProcessor&           processor_ref_;
    TerraForm::FFT::FftDataBlock  fft_data_buffer_;
    TerraForm::FFT::PathDataArray waveform_data_;

    ColourPicker& colour_picker_;
    juce::Colour  waveform_colour_;

    const float bin_width_;

    float bounds_height_;
    float waveform_height_;
    float waveform_origin_offset_;
    float waveform_width_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
