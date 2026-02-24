#include "ColourPickerButton.h"
#include "GlobalConstants.h"

/*---------------------------------------------------------------------------
**
*/
ColourPickerButton::ColourPickerButton(ColourPicker& colour_picker)
    : juce::Button("colour_picker_button")
    , colour_picker_(colour_picker)
{
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    colour_picker_.addChangeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
ColourPickerButton::~ColourPickerButton()
{
    colour_picker_.removeChangeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
ColourPickerButton::paintButton(juce::Graphics& g, bool should_draw_button_as_highlighted, bool should_draw_button_as_down)
{
    juce::ignoreUnused(should_draw_button_as_highlighted, should_draw_button_as_down);

    g.setColour(colour_picker_.getCurrentColour());
    g.fillEllipse(getLocalBounds().toFloat());
}

/*---------------------------------------------------------------------------
**
*/
void
ColourPickerButton::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &colour_picker_) {
        repaint();
    }
}

/*---------------------------------------------------------------------------
** End of File
*/
