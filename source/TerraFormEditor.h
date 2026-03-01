#pragma once

#include <JuceHeader.h>

#include "ColourPicker.h"
#include "ColourPickerButton.h"
#include "TerraFormProcessor.h"
#include "WaveformDisplay.h"

class TerraFormEditor final : public juce::AudioProcessorEditor
{
public:
    explicit TerraFormEditor(TerraFormProcessor& p);
    ~TerraFormEditor() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void showColourPicker();

    enum {
        INITIAL_WIDTH  = 1024,
        INITIAL_HEIGHT = 512,
        MIN_WIDTH      = 156,
        MIN_HEIGHT     = 64,
        PADDING        = 8,
        CPB_DIAMETER   = 16,  //! Colour picker button.
    };

    TerraFormProcessor& processor_ref_;
    ColourPicker        colour_picker_;
    ColourPickerButton  colour_picker_button_;
    WaveformDisplay     waveform_display_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TerraFormEditor)
};
