#include "TerraFormEditor.h"
#include "TerraFormProcessor.h"

/*---------------------------------------------------------------------------
**
*/
TerraFormEditor::TerraFormEditor(TerraFormProcessor& p)
    : juce::AudioProcessorEditor(&p)
    , processor_ref_(p)
    , waveform_display_(p)
{
    addAndMakeVisible(waveform_display_);

    setSize(1024, 512);
    setResizable(true, true);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormEditor::paint(juce::Graphics& g)
{
    g.fillAll(TerraForm::Colours::BACKGROUND_COLOUR);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormEditor::resized()
{
    const auto& bounds = getLocalBounds();
    waveform_display_.setBounds(bounds.withSizeKeepingCentre(bounds.getWidth() * 0.8, bounds.getHeight() * 0.8));
}

/*---------------------------------------------------------------------------
** End of File
*/
