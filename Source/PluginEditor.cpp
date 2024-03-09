/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitCrusherAudioProcessorEditor::BitCrusherAudioProcessorEditor (BitCrusherAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    crushSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    crushSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    crushSlider.setRange(2, 16, 1);
    crushSlider.setValue(16);
    crushSlider.addListener(this);

    rateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    rateSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    rateSlider.setRange(1, 20, 0.1);
    rateSlider.setValue(1);
    rateSlider.addListener(this);

    addAndMakeVisible(crushSlider);
    addAndMakeVisible(rateSlider);
}

BitCrusherAudioProcessorEditor::~BitCrusherAudioProcessorEditor()
{
}

//==============================================================================
void BitCrusherAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void BitCrusherAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();

    auto crushSliderArea = bounds.removeFromTop(25);
    crushSliderArea.setHeight(bounds.getHeight() / 2);
    crushSlider.setBounds(crushSliderArea);

    bounds.removeFromTop(25 + bounds.getHeight() / 2);
    auto rateSliderArea = bounds;
    rateSliderArea.setHeight(bounds.getHeight() / 2);

    rateSlider.setBounds(rateSliderArea);
}

void BitCrusherAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &crushSlider) {
        audioProcessor.crushAmt = 2.0 / 
            (pow(2.0, crushSlider.getValue() - 1.0));
    }
}
