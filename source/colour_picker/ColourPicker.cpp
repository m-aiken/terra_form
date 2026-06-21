#include "ColourPicker.h"
#include "GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
ColourPicker::ColourPicker()
    : juce::ColourSelector(FLAGS, EDGE_GAP, GAP_AROUND_COLOUR_SPACE_COMPONENT)
{
    setColour(backgroundColourId, terra_form::colours::BACKGROUND_COLOUR);
    setCurrentColour(terra_form::colours::DEFAULT_WAVEFORM_COLOUR);
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

/*---------------------------------------------------------------------------
** End of File
*/
