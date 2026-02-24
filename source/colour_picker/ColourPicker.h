#pragma once

#include <JuceHeader.h>

class ColourPicker final : public juce::ColourSelector
{
public:
    ColourPicker();

private:
    enum {
        FLAGS                             = (showColourAtTop | editableColour | showColourspace),
        EDGE_GAP                          = 0,
        GAP_AROUND_COLOUR_SPACE_COMPONENT = 8,
        DEFAULT_WIDTH                     = 320,
        DEFAULT_HEIGHT                    = 256,
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ColourPicker)
};
