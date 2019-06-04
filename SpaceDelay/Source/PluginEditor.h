/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
 */
class SpaceDelayAudioProcessorEditor  : public AudioProcessorEditor, Slider::Listener

{
public:
    
    SpaceDelayAudioProcessorEditor (SpaceDelayAudioProcessor&, AudioProcessorValueTreeState&);
    ~SpaceDelayAudioProcessorEditor();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider* slider) override
     {
     processor.delayTime1 = 250;
     processor.delayTime2 = 500;
     processor.delayTime3 = 750;
     if (slider == &Delay1Slider)
     {
     processor.delayTime1 = (Delay1Slider.getValue() * 1000);
     }
     if (slider == &Delay2Slider)
     {
     processor.delayTime2 = (Delay2Slider.getValue() * 1000);
     }
     if (slider == &Delay3Slider)
     {
     processor.delayTime3 = (Delay3Slider.getValue() * 1000);
     }
     if (slider == &mixSlider)
     {
     processor.Gain = mixSlider.getValue();
     }
     }
        
    
private:
    // Th;is reference is provided as a quick way for your editor to
    // access the processor object that created it.

    double currentTime1 = 250, targetTime1 = 250;
    double currentTime2 = 500, targetTime2 = 500;
    double currentTime3 = 750, targetTime3 = 750;
    double mixLevel = 0.5f, mixTarget = 0.5f;
    
    Image delayimage;
    Image buttonimage;
    ImageButton bypassButton;
    
    Slider Delay1Slider;
    Slider Delay2Slider;
    Slider Delay3Slider;
    Slider mixSlider;
   

    
public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> mixAttachment;
    std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> delay1Attachment;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> delay2Attachment;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> delay3Attachment;
    //creating the attachment to connect my slider to the APVTS




    AudioProcessorValueTreeState& valueTreeState;
    
    SpaceDelayAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpaceDelayAudioProcessorEditor)
};
