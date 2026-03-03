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

    // We only impose a fixed aspect ratio on the main window when
    // the window reaches the minimum size.
    struct {
        const double ASPECT_RATIO = 4.0 / 3.0;  //! 4:3;
        const int    WIDTH        = 320;
        const int    HEIGHT       = static_cast< int >(WIDTH / ASPECT_RATIO);
    } WINDOW_MINIMUM;

    // The waveform bounds have a fixed aspect ratio most of the time,
    // only overridden if the margin around the waveform gets too small.
    static constexpr double WAVEFORM_BOUNDS_ASPECT_RATIO = 4.0 / 1.0;  //! 4:1;

    static constexpr int PADDING      = 8;
    static constexpr int CPB_DIAMETER = 16;  //! Colour picker button.

    ColourPicker       colour_picker_;
    ColourPickerButton colour_picker_button_;
    WaveformDisplay    waveform_display_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TerraFormEditor)
};
