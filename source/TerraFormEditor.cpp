#include "TerraFormEditor.h"
#include "TerraFormProcessor.h"

/*---------------------------------------------------------------------------
**
*/
TerraFormEditor::TerraFormEditor(TerraFormProcessor& p)
    : juce::AudioProcessorEditor(&p)
    , processor_ref_(p)
    , colour_picker_button_(colour_picker_)
    , waveform_display_(p, colour_picker_)
{
    addAndMakeVisible(colour_picker_button_);
    addAndMakeVisible(waveform_display_);

    colour_picker_button_.onClick = [&]() {
        juce::DialogWindow::LaunchOptions opts;

        opts.content                      = { &colour_picker_, false };
        opts.componentToCentreAround      = this;
        opts.escapeKeyTriggersCloseButton = true;

        opts.launchAsync();
    };

    setSize(INITIAL_WIDTH, INITIAL_HEIGHT);
    setResizable(true, true);

    const auto* primary_display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();

    if (primary_display != nullptr) {
        setResizeLimits(MIN_WIDTH, MIN_HEIGHT, primary_display->userArea.getWidth(), primary_display->userArea.getHeight());
    }
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

    colour_picker_button_.setBounds(PADDING, PADDING, ColourPickerButton::DIAMETER, ColourPickerButton::DIAMETER);
    colour_picker_button_.setVisible(bounds.getWidth() > MIN_WIDTH_FOR_CPB && bounds.getHeight() > MIN_HEIGHT_FOR_CPB);
}

/*---------------------------------------------------------------------------
** End of File
*/
