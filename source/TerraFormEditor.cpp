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

    colour_picker_button_.onClick = [&]() { showColourPicker(); };

    setSize(INITIAL_WIDTH, INITIAL_HEIGHT);
    setResizable(true, true);

    if (const auto* primary_display = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
        primary_display != nullptr) {
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
    const auto& bounds                  = getLocalBounds();
    const auto& bounds_width            = bounds.getWidth();
    const auto& bounds_height           = bounds.getHeight();
    const auto& waveform_section_width  = static_cast< int >(static_cast< float >(bounds_width) * 0.8f);
    const auto& waveform_section_height = static_cast< int >(static_cast< float >(bounds_height) * 0.8f);

    waveform_display_.setBounds(bounds.withSizeKeepingCentre(waveform_section_width, waveform_section_height));

    const bool hide_colour_picker = bounds_width < CPB_MIN_WINDOW_WIDTH && bounds_height < CPB_MIN_WINDOW_HEIGHT;
    colour_picker_button_.setBounds(PADDING, PADDING, CPB_DIAMETER, CPB_DIAMETER);
    colour_picker_button_.setVisible(!hide_colour_picker);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormEditor::showColourPicker()
{
    juce::DialogWindow::LaunchOptions opts;

    opts.content                      = { &colour_picker_, false };
    opts.componentToCentreAround      = this;
    opts.escapeKeyTriggersCloseButton = true;

    opts.launchAsync();
}

/*---------------------------------------------------------------------------
** End of File
*/
