#pragma once

#include <JuceHeader.h>

namespace TerraForm
{

static constexpr float MIN_HZ = 20.f;
static constexpr float MAX_HZ = 20000.f;
static constexpr float MIN_DB = -96.f;
static constexpr float MAX_DB = 0.f;

namespace FFT
{

    static constexpr int FFT_ORDER       = 11;
    static constexpr int FFT_SIZE        = 1 << FFT_ORDER;  //! 2048
    static constexpr int NUM_BINS        = FFT_SIZE / 2;
    static constexpr int NUM_PATHS       = 48;
    static constexpr int PATH_RESOLUTION = 1;

    typedef std::array< float, FFT_SIZE * 2 >     FftDataBlock;
    typedef std::array< FftDataBlock, NUM_PATHS > PathDataArray;

}  // namespace FFT

namespace Colours
{

    inline const juce::Colour BACKGROUND_COLOUR       = { 37u, 33u, 38u };     //! Dark grey.
    inline const juce::Colour DEFAULT_WAVEFORM_COLOUR = { 153u, 200u, 202u };  //! Mint blue.

}  // namespace Colours

}  // namespace TerraForm