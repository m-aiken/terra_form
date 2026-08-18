#pragma once

#include <JuceHeader.h>

namespace terra_form
{

inline constexpr float MIN_HZ = 60.f;
inline constexpr float MAX_HZ = 20000.f;
inline constexpr float MIN_DB = -96.f;
inline constexpr float MAX_DB = 0.f;

namespace fft
{

    inline constexpr int FFT_ORDER       = 11;
    inline constexpr int FFT_SIZE        = 1 << FFT_ORDER;  //! 2048
    inline constexpr int NUM_BINS        = FFT_SIZE / 2;
    inline constexpr int NUM_PATHS       = 96;
    inline constexpr int PATH_RESOLUTION = 1;

    typedef std::array< float, FFT_SIZE * 2 >     FftDataBlock;
    typedef std::array< FftDataBlock, NUM_PATHS > PathDataArray;

}  // namespace fft

namespace colours
{

    inline const juce::Colour BACKGROUND_COLOUR       = { 37u, 33u, 38u };    //! Dark grey.
    inline const juce::Colour DEFAULT_WAVEFORM_COLOUR = { 226u, 114u, 91u };  //! Terracotta.

}  // namespace colours

}  // namespace terra_form
