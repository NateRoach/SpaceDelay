/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpaceDelayAudioProcessor::SpaceDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  ),
parameters(*this, nullptr, "SpaceDelay", 
           {
               
               //add list of parameters that you think your plugin will have
               std::make_unique<AudioParameterFloat>(MIX_ID, //Parameter ID
                                                     MIX_NAME, //Parameter Name
                                                     0.0f, //minimum value
                                                     1.0f, //max value
                                                     0.0f //default value
                                                     ),
               
               //not sure if below std thing is necessary for every parameter?
               
               std::make_unique<AudioParameterFloat>(DELAY1_ID,
                                                     DELAY1_NAME,
                                                     0.0f,
                                                     1.0f,
                                                     0.25f),
               
               std::make_unique<AudioParameterFloat>(DELAY2_ID,
                                                     DELAY2_NAME,
                                                     0.0f,
                                                     1.0f,
                                                     0.5f),
               
               std::make_unique<AudioParameterFloat>(DELAY3_ID,
                                                     DELAY3_NAME,
                                                     0.0f,
                                                     1.0f,
                                                     0.75f),
               
               std::make_unique<AudioParameterBool>("bypass", //parameter ID
                                                    "Bypass", //parameter name
                                                    false
                                                    // default state
                                                    )
               
               
           }
           )

#endif
{
    /*float* t = parameters.getRawParameterValue(DELAY1_ID);
    delay1time.setCurrentAndTargetValue(*t);*/
}

SpaceDelayAudioProcessor::~SpaceDelayAudioProcessor()
{
}

//==============================================================================
const String SpaceDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpaceDelayAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SpaceDelayAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SpaceDelayAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SpaceDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpaceDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SpaceDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpaceDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String SpaceDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void SpaceDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SpaceDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    gain.setGainDecibels(0.0f);
    //set the global vairable for what the sample rate is
    mSampleRate = sampleRate;
    //set the delay buffer size so that we can look back in time essentially:
    const int spaceDelayBufferSize = 2*(sampleRate + samplesPerBlock);
    //set global variable for channels:
    const int numInputChannels = getTotalNumInputChannels();
    mSpaceDelayBuffer1.setSize(numInputChannels, spaceDelayBufferSize);
    mSpaceDelayBuffer2.setSize(numInputChannels, spaceDelayBufferSize);
    mSpaceDelayBuffer3.setSize(numInputChannels, spaceDelayBufferSize);
    
    //delay1time.reset(sampleRate, 0.10f);
    
    
    
}

void SpaceDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpaceDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

//============================================================================================================

void SpaceDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    
    
    // store pointer to our parameter
    mixParameter = parameters.getRawParameterValue("mix");
    delay1Parameter = parameters.getRawParameterValue("delay1");
    /*// call delay1time.setTargeValue if new value is different from curren
    // delay1time.setTargetValue(delay1Parameter);*/
    delay2Parameter = parameters.getRawParameterValue("delay2");
    delay3Parameter = parameters.getRawParameterValue("delay3");
    bypassParameter = parameters.getRawParameterValue("bypass");
    
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    



    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear (i, 0, buffer.getNumSamples());
        mSpaceDelayBuffer1.clear (i, 0, mSpaceDelayBuffer1.getNumSamples());
        mSpaceDelayBuffer2.clear (i, 0, mSpaceDelayBuffer2.getNumSamples());
        mSpaceDelayBuffer3.clear (i, 0, mSpaceDelayBuffer3.getNumSamples());
    }
    
    
    // These are getting the number of samples in our audio block and read ffom the main buffer and place it into the delay buffer.  the delay buffer is the same as the main buffer but it is a different length.
    const int bufferLength = buffer.getNumSamples();
    const int spaceDelayBufferLength1 = mSpaceDelayBuffer1.getNumSamples();
    const int spaceDelayBufferLength2 = mSpaceDelayBuffer2.getNumSamples();
    const int spaceDelayBufferLength3 = mSpaceDelayBuffer3.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //read from one buffer and copy it into another
        const float* bufferData = buffer.getReadPointer(channel);
        const float* spaceDelayData1 = mSpaceDelayBuffer1.getReadPointer(channel);
        const float* spaceDelayData3 = mSpaceDelayBuffer2.getReadPointer(channel);
        const float* spaceDelayData2 = mSpaceDelayBuffer3.getReadPointer(channel);
        
        // call the functions declared below.
        fillDelayBuffer(channel, bufferLength, spaceDelayBufferLength1, bufferData, spaceDelayData1);
        fillDelayBuffer2(channel, bufferLength, spaceDelayBufferLength2, bufferData, spaceDelayData2);
        fillDelayBuffer3(channel, bufferLength, spaceDelayBufferLength3, bufferData, spaceDelayData3);
        getFromDelayBuffer(buffer, channel, bufferLength, spaceDelayBufferLength1, bufferData, spaceDelayData1);
        getFromDelayBuffer2(buffer, channel, bufferLength, spaceDelayBufferLength2, bufferData, spaceDelayData2);
        getFromDelayBuffer3(buffer, channel, bufferLength, spaceDelayBufferLength3, bufferData, spaceDelayData3);
        //auto* channelData = buffer.getWritePointer (channel);
        
        
    }
    
     dsp::AudioBlock<float> output(buffer);
     gain.process(dsp::ProcessContextReplacing<float> (output));
    
    
    // Modolo here (%) simple tells this section of code that when the buffer length runs out the next value added into the buffer is 513 not 0.
    mWritePosition += bufferLength;
    mWritePosition %= spaceDelayBufferLength1;
    mWritePosition %= spaceDelayBufferLength2;
    mWritePosition %= spaceDelayBufferLength3;
}

//copy the data from the main buffer to the delay buffer
void SpaceDelayAudioProcessor::fillDelayBuffer(int channel, const int bufferLength, const int spaceDelayBufferLength1, const float* bufferData, const float* spaceDelayData1)
{
    if (spaceDelayBufferLength1 > bufferLength + mWritePosition)
    {
        //copy with ramp means in copying from the main buffer to the delay buffer.
        mSpaceDelayBuffer1.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, Gain, Gain);
    }
    else
    {
        const int bufferRemaining = spaceDelayBufferLength1 - mWritePosition;
        
        mSpaceDelayBuffer1.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, Gain, Gain);
        mSpaceDelayBuffer1.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, Gain, Gain);
    }
    
}

void SpaceDelayAudioProcessor::fillDelayBuffer2(int channel, const int bufferLength, const int spaceDelayBufferLength2, const float* bufferData, const float* spaceDelayData2)
{
    if (spaceDelayBufferLength2 > bufferLength + mWritePosition)
    {
        //copy with ramp means in copying from the main buffer to the delay buffer.
        mSpaceDelayBuffer2.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, Gain, Gain);
    }
    else
    {
        const int bufferRemaining = spaceDelayBufferLength2 - mWritePosition;
        
        mSpaceDelayBuffer2.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, Gain, Gain);
        mSpaceDelayBuffer2.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, Gain, Gain);
    }
    
}

void SpaceDelayAudioProcessor::fillDelayBuffer3(int channel, const int bufferLength, const int spaceDelayBufferLength3, const float* bufferData, const float* spaceDelayData3)
{
    if (spaceDelayBufferLength3 > bufferLength + mWritePosition)
    {
        //copy with ramp means in copying from the main buffer to the delay buffer.
        mSpaceDelayBuffer3.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, Gain, Gain);
    }
    else
    {
        const int bufferRemaining = spaceDelayBufferLength3 - mWritePosition;
        
        mSpaceDelayBuffer3.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, Gain, Gain);
        mSpaceDelayBuffer3.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, Gain, Gain);
    }
    
}


void SpaceDelayAudioProcessor::getFromDelayBuffer (AudioBuffer<float>& buffer, int channel, const int bufferLength, const int spaceDelayBufferLength1, const float* bufferData, const float* spaceDelayData1)
{
    //make sure that this readPosition value is always going to be an int which is why theres a static_cast<int> or something similar in this case **(int)**
    const int readPostion = (int)(spaceDelayBufferLength1 + mWritePosition - (mSampleRate * delayTime1/1000)) % spaceDelayBufferLength1;
    
    if (spaceDelayBufferLength1 > bufferLength + readPostion)
    {
        buffer.addFrom(channel, 0, spaceDelayData1 + readPostion, bufferLength);
    }
    else {
        const int bufferRemaining = spaceDelayBufferLength1 - readPostion;
        buffer.addFrom(channel, 0, spaceDelayData1 + readPostion, bufferRemaining);
        buffer.addFrom(channel, bufferRemaining, spaceDelayData1, bufferLength - bufferRemaining);
    }
}

void SpaceDelayAudioProcessor::getFromDelayBuffer2(AudioBuffer<float>& buffer, int channel, const int bufferLength, const int spaceDelayBufferLength2, const float* bufferData, const float* spaceDelayData2)
{
    //make sure that this readPosition value is always going to be an int which is why theres a static_cast<int>
    const int readPostion = (int)(spaceDelayBufferLength2 + mWritePosition - (mSampleRate * (delayTime2 + delayTime1)/1000)) % spaceDelayBufferLength2;
    
    if (spaceDelayBufferLength2 > bufferLength + readPostion)
    {
        buffer.addFrom(channel, 0, spaceDelayData2 + readPostion, bufferLength);
    }
    else {
        const int bufferRemaining = spaceDelayBufferLength2 - readPostion;
        buffer.addFrom(channel, 0, spaceDelayData2 + readPostion, bufferRemaining);
        buffer.addFrom(channel, bufferRemaining, spaceDelayData2, bufferLength - bufferRemaining);
    }
}

void SpaceDelayAudioProcessor::getFromDelayBuffer3(AudioBuffer<float>& buffer, int channel, const int bufferLength, const int spaceDelayBufferLength3, const float* bufferData, const float* spaceDelayData3)
{
    //make sure that this readPosition value is always going to be an int which is why theres a static_cast<int>
    const int readPostion = (int)(spaceDelayBufferLength3 + mWritePosition - (mSampleRate * (delayTime3+delayTime2+delayTime1)/1000)) % spaceDelayBufferLength3;
    
    if (spaceDelayBufferLength3 > bufferLength + readPostion)
    {
        buffer.addFrom(channel, 0, spaceDelayData3 + readPostion, bufferLength);
    }
    else {
        const int bufferRemaining = spaceDelayBufferLength3 - readPostion;
        buffer.addFrom(channel, 0, spaceDelayData3 + readPostion, bufferRemaining);
        buffer.addFrom(channel, bufferRemaining, spaceDelayData3, bufferLength - bufferRemaining);
    }
}




//==============================================================================
bool SpaceDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SpaceDelayAudioProcessor::createEditor()
{
    return new SpaceDelayAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void SpaceDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState(); //saves valueTree in to "state"
    std::unique_ptr<XmlElement> xml(state.createXml()); //creates an XML version of "state"
    copyXmlToBinary(*xml, destData);
}

void SpaceDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
    
    if(xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            parameters.replaceState(ValueTree::fromXml(*xmlState));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpaceDelayAudioProcessor();
}
