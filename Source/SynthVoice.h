/*
  ==============================================================================

    SynthVoice.h
    Created: 25 May 2018 8:31:52am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "Maximilian/maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast <SynthSound*> (sound) != nullptr;
    }
    
    void getOscType(float* selection)
    {
        if (*selection == 1)
        {
            theWave = 1;
        }
        else if (*selection == 2)
        {
            theWave = 2;
        }
        else if (*selection == 3)
        {
            theWave = 3;
        }
        else if (*selection == 4)
        {
            theWave = 4;
        }
        else
        {
            theWave = 1;
        }
    }
    
    double setOscType ()
    {
        if (theWave == 1)
        {
            return osc1.sinewave(frequency);
        }
        
        if (theWave == 2)
        {
            return osc1.saw(frequency);
        }
        
        if (theWave == 3)
        {
            return osc1.square(frequency);
        }
        
        if (theWave == 4)
        {
            return osc1.triangle(frequency);
        }
        else
        {
            return osc1.sinewave(frequency);
        }
    }
    
    // Saved for later
    //=======================================================
    void setEnvelopeParams(double* attack, double* decay, double* sustain, double* release)
    {
        env1.setAttack(*attack);
        env1.setDecay(*decay);
        env1.setSustain(*sustain);
        env1.setRelease(*release);
    }
    
    //=======================================================
    
    double setEnvelope()
    {
        return env1.adsr(setOscType(), env1.trigger) * level;
    }
    
    //=======================================================
    
    void setFilterParams (float* filterType, float* filterCutoff, float* filterRes)
    {
        filterChoice = *filterType;
        cutoff = *filterCutoff;
        resonance = *filterRes;
    }
    
    double setFilter () // The bandpass filter was removed because it doesn't work
    {
        if (filterChoice == 1)
        {
            return fil1.lores(setEnvelope(), cutoff, resonance);
        }
        else if (filterChoice == 2)
        {
            return fil1.hires(setEnvelope(), cutoff, resonance);
        }
        else if (filterChoice == 3)
        {
            return setEnvelope();
        }
        else
        {
            return setEnvelope();
        }
    }
    //=======================================================
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int) override
    {
        env1.trigger = 1;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
    }
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if (velocity == 0)
            clearCurrentNote();
    }
    
    void pitchWheelMoved (int) override
    {
        
    }
    void controllerMoved (int, int) override
    {
        
    }
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, setFilter());
                
            }
            ++startSample;
        }
    }
    
    int theWave = 1;
    
private:
    double level;
    double frequency;
    
    int filterChoice;
    float cutoff;
    float resonance;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter fil1;
};
