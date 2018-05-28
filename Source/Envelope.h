/*
  ==============================================================================

    Envelope.h
    Created: 25 May 2018 8:31:36am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope();
    ~Envelope();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void attackChanged();
    void decayChanged();
    void sustainChanged();
    void releaseChanged();
    
    double* attackVal_P;
    double* decayVal_P;
    double* sustainVal_P;
    double* releaseVal_P;
    
private:
    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;
    
    double attackVal;
    double decayVal;
    double sustainVal;
    double releaseVal;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
