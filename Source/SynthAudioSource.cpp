/*
  ==============================================================================

    SynthAudioSource.cpp
    Created: 25 May 2018 8:30:54am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthAudioSource.h"

//==============================================================================
SynthAudioSource::SynthAudioSource(MidiKeyboardState& keyState, Envelope& envInit, Oscillator& oscInit, Filter& filInit) : keyboardState(keyState)
{
    synth.clearVoices();
    for (auto i = 0; i < 3; ++i)
    {
        synth.addVoice (new SynthVoice());
        
    }
    synth.clearSounds();
    synth.addSound (new SynthSound());
    env = &envInit;
    osc = &oscInit;
    fil = &filInit;

}

SynthAudioSource::~SynthAudioSource()
{
}

void SynthAudioSource::setUsingSineWaveSound()
{
    synth.clearSounds();
}

void SynthAudioSource::prepareToPlay(int, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    midiCollector.reset(sampleRate);
}

void SynthAudioSource::releaseResources()
{
    
}

void SynthAudioSource::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    
    //get the voice and get the params needed to make the voice
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        //if voice sucessfully casts as a SynthVoice*, get the voice and set the params
        if ((voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))))
        {
            voice->setEnvelopeParams(env->attackVal_P,
                                     env->decayVal_P,
                                     env->sustainVal_P,
                                     env->releaseVal_P);
            
            voice->getOscType(osc->waveSelection_P);
            
            voice->setFilterParams(fil->filterTypeSelection_p,
                                   fil->filterCutoffValue_p,
                                   fil->filterResValue_p);
        }
    }
    
    MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
    keyboardState.processNextMidiBuffer (incomingMidi, bufferToFill.startSample,
                                         bufferToFill.numSamples, true);
    
    synth.renderNextBlock (*bufferToFill.buffer, incomingMidi,
                           bufferToFill.startSample, bufferToFill.numSamples);
}
