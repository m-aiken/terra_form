#include "ColourPicker.h"
#include "GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
ColourPicker::ColourPicker()
    : juce::ColourSelector(FLAGS, EDGE_GAP, GAP_AROUND_COLOUR_SPACE_COMPONENT)
{
    setColour(backgroundColourId, TerraForm::Colours::BACKGROUND_COLOUR);
    setCurrentColour(TerraForm::Colours::DEFAULT_WAVEFORM_COLOUR);
    setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

/*---------------------------------------------------------------------------
** End of File
*/
