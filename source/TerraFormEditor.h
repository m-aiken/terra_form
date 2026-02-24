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
    TerraFormProcessor& processor_ref_;
    ColourPicker        colour_picker_;
    ColourPickerButton  colour_picker_button_;
    WaveformDisplay     waveform_display_;

    enum {
        INITIAL_WIDTH  = 1024,
        INITIAL_HEIGHT = 512,

        MIN_WIDTH  = 156,
        MIN_HEIGHT = 64,
        // Max width/height are calculated from the monitor size.

        // Below a certain window size the colour picker button
        // takes up to high a proportion of the window. Hide it.
        MIN_WIDTH_FOR_CPB  = 320,
        MIN_HEIGHT_FOR_CPB = 160,

        PADDING = 8,
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TerraFormEditor)
};
