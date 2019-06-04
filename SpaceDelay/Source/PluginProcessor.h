/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define MIX_ID "mix"
#define MIX_NAME "Mix"

#define DELAY1_ID "delay1"
#define DELAY1_NAME "Delay"

#define DELAY2_ID "delay2"
#define DELAY2_NAME "Delay2"


#define DELAY3_ID "delay3"
#define DELAY3_NAME "Delay3"

//==============================================================================
/**
 */
class SpaceDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SpaceDelayAudioProcessor();
    ~SpaceDelayAudioProcessor();
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;
    
    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void fillDelayBuffer(int channel, const int bufferLength, const int spaceDelayBufferLength1, const float* bufferData, const float* spaceDelayData1);
    void fillDelayBuffer2(int channel, const int bufferLength, const int spaceDelayBufferLength2, const float* bufferData, const float* spaceDelayData2);
    void fillDelayBuffer3(int channel, const int bufferLength, const int spaceDelayBufferLength3, const float* bufferData, const float* spaceDelayData3);
    
    
    void getFromDelayBuffer(AudioBuffer<float>& buffer, int channel, const int bufferLength, const int spaceDelayBufferLength1, const float* bufferData, const float* spaceDelayData1);
    void getFromDelayBuffer2(AudioBuffer<float>& buffer, int channel, const int bufferLength, const int spaceDelayBufferLength2, const float* bufferData, const float* spaceDelayData2);
    void getFromDelayBuffer3(AudioBuffer<float>& buffer, int channel, const int bufferLength, const int spaceDelayBufferLength3, const float* bufferData, const float* spaceDelayData3);
    
    int delayTime1;
    int delayTime2;
    int delayTime3;
    
    float Gain;
    
    float* mixParameter = nullptr;
    float* bypassParameter = nullptr;
    float* delay1Parameter = nullptr;
    float* delay2Parameter = nullptr;
    float* delay3Parameter = nullptr;
    
    AudioProcessorValueTreeState parameters;
    
    //SmoothedValue<float> delay1time;
    
    float PrevGain;
    
    dsp::Gain<float> gain;
    
    
private:
    AudioBuffer<float> mSpaceDelayBuffer1;
    AudioBuffer<float> mSpaceDelayBuffer2;
    AudioBuffer<float> mSpaceDelayBuffer3;
    int mWritePosition { 0 };
    int mSampleRate { 44100 };
    

    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpaceDelayAudioProcessor)
};
