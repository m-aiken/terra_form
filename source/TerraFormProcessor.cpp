#include "TerraFormEditor.h"
#include "TerraFormProcessor.h"

/*---------------------------------------------------------------------------
**
*/
TerraFormProcessor::TerraFormProcessor()
    : juce::AudioProcessor(BusesProperties()
                               .withInput("Input", juce::AudioChannelSet::stereo(), true)
                               .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

/*---------------------------------------------------------------------------
**
*/
const juce::String
TerraFormProcessor::getName() const
{
    return JucePlugin_Name;
}

/*---------------------------------------------------------------------------
**
*/
bool
TerraFormProcessor::acceptsMidi() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
bool
TerraFormProcessor::producesMidi() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
bool
TerraFormProcessor::isMidiEffect() const
{
    return false;
}

/*---------------------------------------------------------------------------
**
*/
double
TerraFormProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

/*---------------------------------------------------------------------------
**
*/
int
TerraFormProcessor::getNumPrograms()
{
    return 1;  // NB: some hosts don't cope very well if you tell them there are 0 programs,
               // so this should be at least 1, even if you're not really implementing programs.
}

/*---------------------------------------------------------------------------
**
*/
int
TerraFormProcessor::getCurrentProgram()
{
    return 0;
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormProcessor::setCurrentProgram(int index)
{
    juce::ignoreUnused(index);
}

/*---------------------------------------------------------------------------
**
*/
const juce::String
TerraFormProcessor::getProgramName(int index)
{
    juce::ignoreUnused(index);

    return {};
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormProcessor::changeProgramName(int index, const juce::String& new_name)
{
    juce::ignoreUnused(index, new_name);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormProcessor::prepareToPlay(double sample_rate, int samples_per_block)
{
    juce::ignoreUnused(sample_rate, samples_per_block);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

/*---------------------------------------------------------------------------
**
*/
bool
TerraFormProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Some plugin hosts will only support mono or stereo output bus layouts.
    const bool mono_out   = layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono();
    const bool stereo_out = layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();

    // We want the input and output layouts to match (i.e. mono in --> mono out or stereo in --> stereo out).
    const bool in_matches_out = layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();

    return (mono_out || stereo_out) && in_matches_out;
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormProcessor::processBlock(juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midi_messages)
{
    juce::ignoreUnused(midi_messages);

    juce::ScopedNoDenormals no_denormals;
    const auto              num_input_channels  = getTotalNumInputChannels();
    const auto              num_output_channels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, clear any output channels that don't contain input data.
    for (auto i = num_input_channels; i < num_output_channels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        fft_block_producer_.pushSample(buffer.getSample(0, i));
    }
}

/*---------------------------------------------------------------------------
**
*/
bool
TerraFormProcessor::hasEditor() const
{
    return true;
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessorEditor*
TerraFormProcessor::createEditor()
{
    return new TerraFormEditor(*this);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormProcessor::getStateInformation(juce::MemoryBlock& dest_data)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused(dest_data);
}

/*---------------------------------------------------------------------------
**
*/
void
TerraFormProcessor::setStateInformation(const void* data, int size_in_bytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused(data, size_in_bytes);
}

/*---------------------------------------------------------------------------
**
*/
juce::AudioProcessor* JUCE_CALLTYPE
createPluginFilter()
{
    return new TerraFormProcessor();
}

/*---------------------------------------------------------------------------
** End of File
*/
