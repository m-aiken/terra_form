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

    static constexpr int INITIAL_WIDTH  = 1024;
    static constexpr int INITIAL_HEIGHT = 512;
    static constexpr int MIN_WIDTH      = 156;  //! Max is calculated from the monitor size.
    static constexpr int MIN_HEIGHT     = 64;   //! Max is calculated from the monitor size.

    static constexpr int PADDING = 8;

    // Below a certain window size the colour picker button
    // takes up too high a proportion of the window. Hide it.
    static constexpr int CPB_MIN_WINDOW_WIDTH  = 320;
    static constexpr int CPB_MIN_WINDOW_HEIGHT = 160;
    static constexpr int CPB_DIAMETER          = 16;

    void showColourPicker();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TerraFormEditor)
};
