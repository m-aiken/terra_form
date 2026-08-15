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
    setSize(WINDOW_MINIMUM.WIDTH * 3, static_cast< int >(WINDOW_MINIMUM.HEIGHT * 2.5));
    setResizable(true, true);
    getConstrainer()->setMinimumSize(WINDOW_MINIMUM.WIDTH, WINDOW_MINIMUM.HEIGHT);

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
    g.fillAll(terra_form::colours::BACKGROUND_COLOUR);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormEditor::resized()
{
    const auto& bounds                 = getLocalBounds().toDouble();
    const auto& waveform_bounds_width  = bounds.getWidth() * 0.8;
    auto        waveform_bounds_height = waveform_bounds_width / WAVEFORM_BOUNDS_ASPECT_RATIO;

    // Ensure we maintain at least a minimum margin (PADDING * n) around the waveform container.
    waveform_bounds_height = juce::jmin(waveform_bounds_height, bounds.getHeight() - (PADDING * 8.0));

    waveform_display_.setBounds(
        bounds.withSizeKeepingCentre(waveform_bounds_width, waveform_bounds_height).toNearestInt());

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
