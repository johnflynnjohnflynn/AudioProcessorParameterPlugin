/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AudioProcessParameterPluginAudioProcessor::AudioProcessParameterPluginAudioProcessor()
{

    // We addParameter() to the processor's OwnedArray<AudioProcessorParameter>
    // managedParameters, which takes ownership and deletes appropriately
    addParameter (boolParam_   = new AudioParameterBool {"BoolID", "Bool", false});

    constexpr int defaultChoiceIndex = 0;
    choiceStrings.add ("First option");
    choiceStrings.add ("Another...");
    choiceStrings.add ("A third option");
    addParameter (choiceParam_ = new AudioParameterChoice {"ChoiceID", "Choice", choiceStrings, defaultChoiceIndex});

    addParameter (floatParam_  = new AudioParameterFloat {"FloatID", "Float", -24.0f, 0.0f, 0.0f});
    addParameter (intParam_    = new AudioParameterInt   {"IntID",   "Int",   -64,   63,    0});
}

AudioProcessParameterPluginAudioProcessor::~AudioProcessParameterPluginAudioProcessor()
{
}

//==============================================================================
const String AudioProcessParameterPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioProcessParameterPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioProcessParameterPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double AudioProcessParameterPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioProcessParameterPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioProcessParameterPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioProcessParameterPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String AudioProcessParameterPluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void AudioProcessParameterPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AudioProcessParameterPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AudioProcessParameterPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void AudioProcessParameterPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    // Do nothing i.e. "pass the audio through the plugin".

}

//==============================================================================
bool AudioProcessParameterPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AudioProcessParameterPluginAudioProcessor::createEditor()
{
    return new AudioProcessParameterPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AudioProcessParameterPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    // You should use this method to store your parameters in the memory block.
    // Here's an example of how you can use XML to make it easy and more robust:

    // Create an outer XML element..
    XmlElement xml ("MYPLUGINSETTINGS");

    // Store the values of all our parameters, using their param ID as the XML attribute
    for (int i = 0; i < getNumParameters(); ++i)
        if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
            xml.setAttribute (p->paramID, p->getValue());

    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void AudioProcessParameterPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // Now reload our parameters..
            for (int i = 0; i < getNumParameters(); ++i)
                if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
                    p->setValueNotifyingHost ((float) xmlState->getDoubleAttribute (p->paramID, p->getValue()));
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioProcessParameterPluginAudioProcessor();
}
