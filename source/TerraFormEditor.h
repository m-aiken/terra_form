#pragma once

#include <JuceHeader.h>

#include "TerraFormProcessor.h"

class TerraFormEditor final : public juce::AudioProcessorEditor
{
public:
    explicit TerraFormEditor(TerraFormProcessor& p);
    ~TerraFormEditor() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    TerraFormProcessor& processor_ref_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TerraFormEditor)
};
