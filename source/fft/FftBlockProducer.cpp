#include "FftBlockProducer.h"

/*---------------------------------------------------------------------------
**
*/
FftBlockProducer::FftBlockProducer()
    : fft_(TerraForm::FFT::FFT_ORDER)
    , windowing_function_(TerraForm::FFT::FFT_SIZE, juce::dsp::WindowingFunction< float >::hann)
    , fifo_()
    , fifo_index_(0)
    , fft_data_()
    , next_block_ready_(false)
{
}

/*---------------------------------------------------------------------------
**
*/
void
FftBlockProducer::pushSample(const float sample)
{
    if (fifo_index_ == TerraForm::FFT::FFT_SIZE) {
        if (!next_block_ready_) {
            std::fill(fft_data_.begin(), fft_data_.end(), 0.f);
            std::copy(fifo_.begin(), fifo_.end(), fft_data_.begin());
            performFft(fft_data_);

            next_block_ready_ = true;
        }

        // Reset the fifo index.
        fifo_index_ = 0;
    }

    fifo_[fifo_index_++] = sample;
}

/*---------------------------------------------------------------------------
**
*/
bool
FftBlockProducer::nextBlockReady() const
{
    return next_block_ready_;
}

/*---------------------------------------------------------------------------
**
*/
TerraForm::FFT::FftDataBlock&
FftBlockProducer::getNextBlock()
{
    next_block_ready_ = false;

    return fft_data_;
}

/*---------------------------------------------------------------------------
**
*/
void
FftBlockProducer::performFft(TerraForm::FFT::FftDataBlock& fft_data) const
{
    using namespace TerraForm::FFT;

    windowing_function_.multiplyWithWindowingTable(fft_data.data(), FFT_SIZE);
    fft_.performFrequencyOnlyForwardTransform(fft_data.data());

    juce::FloatVectorOperations::multiply(fft_data.data(), 1.f / static_cast< float >(NUM_BINS), NUM_BINS + 1);

    for (auto& val : fft_data) {
        val = juce::Decibels::gainToDecibels(val, TerraForm::MIN_DB);
    }
}

/*---------------------------------------------------------------------------
** End of File
*/