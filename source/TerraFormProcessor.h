#pragma once

#include <JuceHeader.h>

class TerraFormProcessor final : public juce::AudioProcessor
{
public:
    TerraFormProcessor();
    ~TerraFormProcessor() override = default;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;

    double getTailLengthSeconds() const override;

    int                getNumPrograms() override;
    int                getCurrentProgram() override;
    void               setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void               changeProgramName(int index, const juce::String& new_name) override;

    void prepareToPlay(double sample_rate, int samples_per_block) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer< float >& buffer, juce::MidiBuffer& midi_messages) override;
    // using AudioProcessor::processBlock;

    bool                        hasEditor() const override;
    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& dest_data) override;
    void setStateInformation(const void* data, int size_in_bytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TerraFormProcessor)
};
