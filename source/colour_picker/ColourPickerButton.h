#pragma once

#include <JuceHeader.h>

#include "ColourPicker.h"

class ColourPickerButton final
    : public juce::Button
    , public juce::ChangeListener
{
public:
    explicit ColourPickerButton(ColourPicker& colour_picker);
    ~ColourPickerButton() override;

    void paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down) override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    ColourPicker& colour_picker_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColourPickerButton)
};
