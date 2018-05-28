/*
  ==============================================================================

    Filter.h
    Created: 25 May 2018 8:31:21am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter();
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;
    
    void filterMenuChanged();
    void filterCutoffChanged();
    void filterResChanged();
    
    float filterTypeSelection;
    float* filterTypeSelection_p;
    
    float filterCutoffValue;
    float* filterCutoffValue_p;
    
    float filterResValue;
    float* filterResValue_p;

private:
    Slider filterCutoff;
    Slider filterRes;
    
    ComboBox filterMenu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
