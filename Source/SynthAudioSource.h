/*
  ==============================================================================

    SynthAudioSource.h
    Created: 25 May 2018 8:30:54am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"
#include "SynthSound.h"
#include "Oscillator.h"
#include "Envelope.h"
#include "Filter.h"

//==============================================================================
/*
*/
class SynthAudioSource    : public AudioSource
{
public:
    SynthAudioSource(MidiKeyboardState& keyState, Envelope& envInit, Oscillator& oscInit, Filter& filInit);
    ~SynthAudioSource();

    void prepareToPlay (int, double sampleRate) override;
    void releaseResources () override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    MidiMessageCollector* getMidiCollector()
    {
        return &midiCollector;
    }
    
    // I dont think i need this function. Delete if necessary
    void setUsingSineWaveSound ();
    
    SynthVoice* voice;
    Envelope* env;
    Oscillator* osc;
    Filter* fil;

private:
    MidiKeyboardState& keyboardState;
    Synthesiser synth;
    MidiMessageCollector midiCollector;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthAudioSource)
};
