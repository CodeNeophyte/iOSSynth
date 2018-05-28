/*
  ==============================================================================

    Oscillator.h
    Created: 25 May 2018 8:31:12am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class Oscillator : public Component,
                    private ComboBox::Listener
{
public:
    Oscillator();
    ~Oscillator();
    
    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged (ComboBox*) override;
    void oscMenuChanged();
    
    float waveSelection;
    float* waveSelection_P;
    
private:
    ComboBox oscMenu;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
