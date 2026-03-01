#include "TerraFormEditor.h"
#include "TerraFormProcessor.h"

/*---------------------------------------------------------------------------
**
*/
TerraFormEditor::TerraFormEditor(TerraFormProcessor& p)
    : juce::AudioProcessorEditor(&p)
    , colour_picker_button_(colour_picker_)
    , waveform_display_(p, colour_picker_)
{
    setSize(INITIAL_WIDTH, INITIAL_HEIGHT);
    setResizable(true, true);

    // Set the resize limits based on the monitor size.
    if (const auto* monitor = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay(); monitor != nullptr) {
        setResizeLimits(MIN_WIDTH, MIN_HEIGHT, monitor->userArea.getWidth(), monitor->userArea.getHeight());
    }

    // Set the main window to use the native OS title bar.
    if (auto* main_window = juce::TopLevelWindow::getTopLevelWindow(0); main_window != nullptr) {
        main_window->setUsingNativeTitleBar(true);
    }

    addAndMakeVisible(colour_picker_button_);
    addAndMakeVisible(waveform_display_);

    colour_picker_button_.setAlwaysOnTop(true);
    colour_picker_button_.onClick = [&]() { showColourPicker(); };
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
    const auto& bounds_i                = getLocalBounds();
    const auto& bounds_f                = getLocalBounds().toFloat();
    const auto& waveform_section_width  = static_cast< int >(bounds_f.getWidth() * 0.8f);
    const auto& waveform_section_height = static_cast< int >(bounds_f.getHeight() * 0.8f);

    waveform_display_.setBounds(bounds_i.withSizeKeepingCentre(waveform_section_width, waveform_section_height));

    colour_picker_button_.setBounds(PADDING, PADDING, CPB_DIAMETER, CPB_DIAMETER);
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
