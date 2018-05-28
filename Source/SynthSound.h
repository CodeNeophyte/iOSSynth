/*
  ==============================================================================

    SynthSound.h
    Created: 25 May 2018 8:32:01am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#pragma once

class SynthSound : public SynthesiserSound
{
public:
//    SynthSound();
    
    bool appliesToNote (int) override
    {
        return true;
    }
    bool appliesToChannel (int) override
    {
        return true;
    }
};
