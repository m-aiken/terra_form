#pragma once

#include <JuceHeader.h>

namespace TerraForm
{

namespace FFT
{

    static constexpr int FFT_ORDER       = 11;
    static constexpr int FFT_SIZE        = 1 << FFT_ORDER;  //! 2048
    static constexpr int NUM_BINS        = FFT_SIZE / 2;
    static constexpr int NUM_PATHS       = 24;
    static constexpr int PATH_RESOLUTION = 1;

    typedef std::array< float, FFT_SIZE * 2 >     FftDataBlock;
    typedef std::array< juce::Path, NUM_PATHS >   PathArray;
    typedef std::array< FftDataBlock, NUM_PATHS > PathDataArray;

}  // namespace FFT

namespace Colours
{

    inline const juce::Colour                               BACKGROUND_COLOUR = { 37u, 33u, 38u };
    inline const std::array< juce::Colour, FFT::NUM_PATHS > WAVEFORM_COLOURS {
        juce::Colour::fromString("FF9C99CC"),  //!
        juce::Colour::fromString("FF9D9CCC"),  //!
        juce::Colour::fromString("FF9E9FCD"),  //!
        juce::Colour::fromString("FF9EA2CD"),  //!
        juce::Colour::fromString("FF9FA5CD"),  //!
        juce::Colour::fromString("FFA0A8CD"),  //!
        juce::Colour::fromString("FFA1ABCE"),  //!
        juce::Colour::fromString("FFA2AECE"),  //!
        juce::Colour::fromString("FFA3B1CE"),  //!
        juce::Colour::fromString("FFA3B4CE"),  //!
        juce::Colour::fromString("FFA4B7CF"),  //!
        juce::Colour::fromString("FFA5BACF"),  //!
        juce::Colour::fromString("FFA6BDCF"),  //!
        juce::Colour::fromString("FFA7C0CF"),  //!
        juce::Colour::fromString("FFA8C3D0"),  //!
        juce::Colour::fromString("FFA8C6D0"),  //!
        juce::Colour::fromString("FFA9C9D0"),  //!
        juce::Colour::fromString("FFAACCD0"),  //!
        juce::Colour::fromString("FFABCFD1"),  //!
        juce::Colour::fromString("FFACD2D1"),  //!
        juce::Colour::fromString("FFADD5D1"),  //!
        juce::Colour::fromString("FFADD8D1"),  //!
        juce::Colour::fromString("FFAEDBD2"),  //!
        juce::Colour::fromString("FFAFDED2"),  //!
    };

}  // namespace Colours

}  // namespace TerraForm