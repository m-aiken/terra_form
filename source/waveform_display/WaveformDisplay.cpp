#include "WaveformDisplay.h"

/*---------------------------------------------------------------------------
**
*/
WaveformDisplay::WaveformDisplay(TerraFormProcessor& p, ColourPicker& colour_picker)
    : processor_ref_(p)
    , waveform_data_()
    , colour_picker_(colour_picker)
    , waveform_colour_(colour_picker_.getCurrentColour())
    , bin_width_(static_cast< float >(processor_ref_.getSampleRate() / static_cast< double >(TerraForm::FFT::FFT_SIZE)))
    , bounds_height_(0.0)
    , waveform_height_(0.0)
    , waveform_origin_offset_(0.0)
    , waveform_width_(0.0)
{
    for (auto& wd : waveform_data_) {
        wd.fill(TerraForm::MIN_DB);
    }

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
WaveformDisplay::resized()
{
    const auto& bounds      = getLocalBounds();
    bounds_height_          = bounds.getHeight();
    waveform_height_        = bounds_height_ * 0.2;
    waveform_origin_offset_ = (bounds_height_ - waveform_height_) / TerraForm::FFT::NUM_PATHS;
    waveform_width_         = bounds.getWidth() - (waveform_origin_offset_ * TerraForm::FFT::NUM_PATHS);
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

    const auto  x_offset          = path_index * waveform_origin_offset_;
    const auto  y_offset          = path_index * waveform_origin_offset_;
    const auto& waveform_x_origin = x_offset;
    const auto& waveform_y_origin = bounds_height_ - y_offset;

    path.clear();
    path.startNewSubPath(waveform_x_origin, waveform_y_origin);

    for (size_t i = 1; i < TerraForm::FFT::NUM_BINS + 1; i += TerraForm::FFT::PATH_RESOLUTION) {
        const auto raw_freq     = (i * bin_width_);
        const auto norm_freq    = juce::mapFromLog10(raw_freq, TerraForm::MIN_HZ, TerraForm::MAX_HZ);
        const auto x_coordinate = std::floor(norm_freq * waveform_width_);

        if (x_coordinate > waveform_width_) {
            continue;
        }

        const auto y_coordinate =
            juce::jmap< float >(fft_data.at(i), TerraForm::MIN_DB, TerraForm::MAX_DB, 0, waveform_height_);

        if (std::isnan(y_coordinate) || std::isinf(y_coordinate)) {
            continue;
        }

        path.lineTo(waveform_x_origin + x_coordinate, waveform_y_origin - y_coordinate);
    }

    return path;
}

/*---------------------------------------------------------------------------
** End of File
*/
