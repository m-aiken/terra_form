#include "WaveformDisplay.h"

/*---------------------------------------------------------------------------
**
*/
WaveformDisplay::WaveformDisplay(TerraFormProcessor& p, ColourPicker& colour_picker)
    : processor_ref_(p)
    , fft_data_buffer_()
    , waveform_data_()
    , colour_picker_(colour_picker)
    , waveform_colour_(colour_picker_.getCurrentColour())
    , bin_width_(static_cast< float >(processor_ref_.getSampleRate() / static_cast< double >(terra_form::fft::FFT_SIZE)))
    , bounds_height_(0.f)
    , waveform_height_(0.f)
    , waveform_origin_offset_(0.f)
    , waveform_width_(0.f)
{
    for (auto& wd : waveform_data_) {
        wd.fill(terra_form::MIN_DB);
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
    for (size_t i = 0; i < terra_form::fft::NUM_PATHS; ++i) {
        const auto& path   = getWaveformPath(waveform_data_.at(i), i);
        const auto& bounds = path.getBounds();

        // Alpha/fade logic:
        // 1. Each path fades from bright peaks to dim valleys.
        // 2. The paths fade off into the distance.
        const auto alpha    = 1.f - (static_cast< float >(i) / static_cast< float >(terra_form::fft::NUM_PATHS));
        const auto gradient = juce::ColourGradient::vertical(waveform_colour_.withAlpha(0.1f * alpha),
                                                             bounds.getCentreY(),
                                                             waveform_colour_.withAlpha(alpha),
                                                             bounds.getY());

        g.setGradientFill(gradient);
        g.strokePath(path, juce::PathStrokeType(1.f));
    }
}

/*---------------------------------------------------------------------------
**
*/
void
WaveformDisplay::resized()
{
    const auto& bounds      = getLocalBounds().toFloat();
    bounds_height_          = bounds.getHeight();
    waveform_height_        = bounds_height_ * 0.2f;
    waveform_origin_offset_ = (bounds_height_ - waveform_height_) / terra_form::fft::NUM_PATHS;
    waveform_width_         = bounds.getWidth() - (waveform_origin_offset_ * terra_form::fft::NUM_PATHS);
}

/*---------------------------------------------------------------------------
**
*/
void
WaveformDisplay::timerCallback()
{
    if (processor_ref_.getFft().nextBlockReady()) {
        // Clear our buffer.
        fft_data_buffer_.fill(0.f);
        // Copy the latest FFT data to our buffer.
        processor_ref_.getFft().getNextBlock(fft_data_buffer_);
        // Push all paths back 1 (rotate the existing path data to the right from begin+1 to end).
        std::rotate(waveform_data_.rbegin(), waveform_data_.rbegin() + 1, waveform_data_.rend());
        // Overwrite the new 1st element with new data.
        waveform_data_.front().swap(fft_data_buffer_);

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
WaveformDisplay::getWaveformPath(const terra_form::fft::FftDataBlock& fft_data, const size_t path_index) const
{
    juce::Path path;

    const auto  x_offset          = static_cast< float >(path_index) * waveform_origin_offset_;
    const auto  y_offset          = static_cast< float >(path_index) * waveform_origin_offset_;
    const auto& waveform_x_origin = x_offset;
    const auto& waveform_y_origin = bounds_height_ - y_offset;

    path.clear();
    path.startNewSubPath(waveform_x_origin, waveform_y_origin);

    for (size_t i = 1; i < terra_form::fft::NUM_BINS + 1; i += terra_form::fft::PATH_RESOLUTION) {
        const auto raw_freq     = (static_cast< float >(i) * bin_width_);
        const auto norm_freq    = juce::mapFromLog10(raw_freq, terra_form::MIN_HZ, terra_form::MAX_HZ);
        const auto x_coordinate = std::floor(norm_freq * waveform_width_);

        if (x_coordinate > waveform_width_) {
            continue;
        }

        const auto y_coordinate =
            juce::jmap< float >(fft_data.at(i), terra_form::MIN_DB, terra_form::MAX_DB, 0, waveform_height_);

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
