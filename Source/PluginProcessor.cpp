/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

// this is a change

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ExampleProjectAudioProcessor::ExampleProjectAudioProcessor()
     : AudioProcessor (BusesProperties()
                     
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                    
                       )
{
}

ExampleProjectAudioProcessor::~ExampleProjectAudioProcessor()
{
}

//==============================================================================
const juce::String ExampleProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ExampleProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ExampleProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ExampleProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ExampleProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ExampleProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ExampleProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ExampleProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ExampleProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void ExampleProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ExampleProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
          *filter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 1000.0f);
   
          juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
          filter.prepare (spec);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ExampleProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ExampleProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void ExampleProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
   // auto totalNumInputChannels  = getTotalNumInputChannels();
   // auto totalNumOutputChannels = getTotalNumOutputChannels();
  //  auto mainInputOutput = getBusBuffer (buffer, true, 0);                                  // [5]
  //  double current, computed;

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
   // for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
     //   buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    //for (int channel = 0; channel < totalNumInputChannels; ++channel)
  //  {
      //  auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
   // }
  //  for (auto j = 0; j < buffer.getNumSamples(); ++j) {                                      // [7]

   
     //   for (auto i = 0; i < mainInputOutput.getNumChannels(); ++i)    {                     // [11]
          //  current = *mainInputOutput.getReadPointer (i, j);
     //       current = mainInputOutput.getSample ( i, j);
       //     computed = current + previous_sample;
  //          previous_sample = current;
     //       mainInputOutput.setSample (i, j, 0);
           // *mainInputOutput.getWritePointer (i, j) = computed;
           // *mainInputOutput.getWritePointer (i, j) = sampleCountDown > 0 ? *mainInputOutput.getReadPointer (i, j)
              //                                                        : 0.0f;
     //   }
   // }
    juce::dsp::AudioBlock<float> block (buffer);
           juce::dsp::ProcessContextReplacing<float> context (block);
           filter.process (context);
}

//==============================================================================
bool ExampleProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ExampleProjectAudioProcessor::createEditor()
{
    return new ExampleProjectAudioProcessorEditor (*this);
}

//==============================================================================
void ExampleProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ExampleProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExampleProjectAudioProcessor();
}
