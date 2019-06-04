/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpaceDelayAudioProcessorEditor::SpaceDelayAudioProcessorEditor(SpaceDelayAudioProcessor& p,AudioProcessorValueTreeState& vts) : AudioProcessorEditor (&p), valueTreeState(vts), processor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    delayimage = ImageCache::getFromMemory(BinaryData::delayimage_jpg, BinaryData::delayimage_jpgSize);
    
    delay1Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "delay1", Delay1Slider);
    delay2Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "delay2", Delay2Slider);
    delay3Attachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "delay3", Delay3Slider);
    mixAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "mix", mixSlider);


    
    setResizable(true, true);
    setSize (400, 600);
    
    Delay1Slider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Delay1Slider.setRange(0.0, 1000.0f);
    Delay2Slider.setMouseDragSensitivity(10);
    //Delay1Slider.setValue(currentTime1, dontSendNotification);
    Delay1Slider.setNumDecimalPlacesToDisplay(2);
    Delay1Slider.setTextValueSuffix(" Seconds");
    Delay1Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, false, 80, 30);
    addAndMakeVisible(Delay1Slider);
    Delay1Slider.addListener(this);
    
    
    
    Delay2Slider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Delay2Slider.setRange(0.0, 1000.0f);
    Delay2Slider.setMouseDragSensitivity(10);
    //Delay2Slider.setValue(currentTime2, dontSendNotification);
    Delay2Slider.setNumDecimalPlacesToDisplay(2);
    Delay2Slider.setTextValueSuffix(" Seconds");
    Delay2Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, false, 80, 30);
    addAndMakeVisible(Delay2Slider);
    Delay2Slider.addListener(this);
    
    
    
    Delay3Slider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    Delay3Slider.setRange(0.0, 1000.0f);
    Delay2Slider.setMouseDragSensitivity(10);
    //Delay3Slider.setValue(currentTime3, dontSendNotification);
    Delay3Slider.setNumDecimalPlacesToDisplay(2);
    Delay3Slider.setTextValueSuffix(" Seconds");
    Delay3Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, false, 80, 30);
    addAndMakeVisible(Delay3Slider);
    Delay3Slider.addListener(this);
    
    
    
    mixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider.setRange(0, 1.0f);
    mixSlider.setValue(mixLevel, dontSendNotification);
    mixSlider.setTextValueSuffix(" % ");
    addAndMakeVisible(mixSlider);
    mixSlider.addListener(this);
    
    
    
    bypassButton.setImages(true, true, true, buttonimage, 1.0f, Colours::darkgrey.withAlpha(0.9f), buttonimage, 0.5f, Colours::grey.withAlpha(0.5f), buttonimage, 1.0f, Colours::white.withAlpha(0.0f));
    bypassAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment (valueTreeState, "bypass", bypassButton));
    addAndMakeVisible(bypassButton);
    
    
    delay1Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "delay1", Delay1Slider));
    delay2Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "delay2", Delay2Slider));
    delay3Attachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "delay3", Delay3Slider));
    mixAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment (valueTreeState, "mix", mixSlider));
}

SpaceDelayAudioProcessorEditor::~SpaceDelayAudioProcessorEditor()
{
    
}

//==============================================================================
void SpaceDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::mediumpurple);
    
    g.drawImageWithin(delayimage, 0, 0, getWidth(), getHeight(), RectanglePlacement::fillDestination);
}

void SpaceDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mixSlider.setBounds(54, getHeight()-170, getWidth()-200, 100);
    
    Delay1Slider.setBounds(-5, getHeight()-370, getWidth()-295, 150);
    Delay2Slider.setBounds(139, getHeight()-370, getWidth()-295, 150);
    Delay3Slider.setBounds(276, getHeight()-370, getWidth()-295, 150);
    
}
