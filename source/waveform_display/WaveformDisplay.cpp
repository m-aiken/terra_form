#include "WaveformDisplay.h"

/*---------------------------------------------------------------------------
**
*/
WaveformDisplay::WaveformDisplay(TerraFormProcessor& p, ColourPicker& colour_picker)
    : processor_ref_(p)
    , waveform_data_()
    , colour_picker_(colour_picker)
    , waveform_colour_(colour_picker_.getCurrentColour())
{
    colour_picker_.addChangeListener(this);
    startTimerHz(60);
}

/*---------------------------------------------------------------------------
**
*/
WaveformDisplay::~WaveformDisplay()
{
    stopTimer();
    colour_picker_.removeChangeListener(this);
}

/*---------------------------------------------------------------------------
**
*/
void
WaveformDisplay::paint(juce::Graphics& g)
{
    for (int i = 0; i < TerraForm::FFT::NUM_PATHS; ++i) {
        // Alpha value: descend from 1 to 0 as we progress through the data.
        const auto alpha = 1.f - (static_cast< float >(i) / static_cast< float >(TerraForm::FFT::NUM_PATHS));

        g.setColour(waveform_colour_.withAlpha(alpha));
        g.strokePath(getWaveformPath(waveform_data_.at(i), i), juce::PathStrokeType(1.f));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
WaveformDisplay::timerCallback()
{
    if (processor_ref_.getFft().nextBlockReady()) {
        const TerraForm::FFT::FftDataBlock& fft_data = processor_ref_.getFft().getNextBlock();

        // Push all paths back 1 (rotate the existing path data to the right from begin+1 to end).
        std::rotate(waveform_data_.rbegin(), waveform_data_.rbegin() + 1, waveform_data_.rend());

        // Overwrite the new 1st element with new data.
        waveform_data_[0] = fft_data;

        repaint();
    }
}

/*---------------------------------------------------------------------------
**
*/
void
WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &colour_picker_) {
        waveform_colour_ = colour_picker_.getCurrentColour();
    }
}

/*---------------------------------------------------------------------------
**
*/
juce::Path
WaveformDisplay::getWaveformPath(const TerraForm::FFT::FftDataBlock& fft_data, const int path_index) const
{
    juce::Path path;

    const auto& full_bounds        = getLocalBounds();
    const auto& full_bounds_width  = full_bounds.getWidth();
    const auto& full_bounds_height = full_bounds.getHeight();
    const auto& waveform_height    = full_bounds_height * 0.2;
    const auto& offset             = (full_bounds_height - waveform_height) / TerraForm::FFT::NUM_PATHS;
    const auto& waveform_width     = full_bounds_width - (offset * TerraForm::FFT::NUM_PATHS);
    const auto& x_offset           = path_index * offset;
    const auto& y_offset           = path_index * offset;

    const auto& drawable_bounds = full_bounds.withHeight(full_bounds_height - waveform_height).withY(waveform_height);
    const auto& drawable_bounds_height = drawable_bounds.getHeight();

    const auto& waveform_bounds =
        juce::Rectangle< int >(x_offset, drawable_bounds_height - y_offset, waveform_width, waveform_height);

    const auto& waveform_bounds_left   = waveform_bounds.getX();
    const auto& waveform_bounds_bottom = waveform_bounds.getBottom();

    const float bin_width = static_cast< float >(getBinWidth());

    path.clear();
    path.startNewSubPath(waveform_bounds_left, waveform_bounds_bottom);

    for (size_t i = 1; i < TerraForm::FFT::NUM_BINS + 1; i += TerraForm::FFT::PATH_RESOLUTION) {
        const auto raw_freq     = (i * bin_width);
        const auto norm_freq    = juce::mapFromLog10(raw_freq, 20.f, 20000.f);
        const auto x_coordinate = std::floor(norm_freq * waveform_width);

        if (x_coordinate > waveform_width) {
            continue;
        }

        const auto y_coordinate = getYCoordinate(fft_data.at(i), waveform_height);

        if (std::isnan(y_coordinate) || std::isinf(y_coordinate)) {
            continue;
        }

        path.lineTo(waveform_bounds_left + x_coordinate, waveform_bounds_bottom - y_coordinate);
    }

    // path.lineTo(width, bounds_height);

    return path;
}

/*---------------------------------------------------------------------------
**
*/
/*static*/ float
WaveformDisplay::getYCoordinate(const float& sample, const int& dest_height)
{
    return juce::jmap< float >(sample, -100.f, 0.f, 0, dest_height);
}

/*---------------------------------------------------------------------------
**
*/
double
WaveformDisplay::getBinWidth() const
{
    return processor_ref_.getSampleRate() / static_cast< double >(TerraForm::FFT::FFT_SIZE);
}

/*---------------------------------------------------------------------------
** End of File
*/
