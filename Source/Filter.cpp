/*
  ==============================================================================

    Filter.cpp
    Created: 25 May 2018 8:31:21am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter()
{
    setSize(200, 200);
    
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("None", 3);
    filterMenu.setJustificationType(Justification::centred);
    addAndMakeVisible(&filterMenu);
    
    filterMenu.onChange = [this] { filterMenuChanged(); };
    filterMenu.setSelectedId(3);
    
    filterTypeSelection = 3;
    filterTypeSelection_p = &filterTypeSelection;

    filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0, 10000.0);
    filterCutoff.setValue(400.0);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterCutoff);
    filterCutoff.onValueChange = [this] { filterCutoffChanged(); };
    filterCutoff.setSkewFactorFromMidPoint(1000.0);
    
    filterCutoffValue = filterCutoff.getValue();
    filterCutoffValue_p = &filterCutoffValue;
    
    filterRes.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1, 5);
    filterRes.setValue(1);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(&filterRes);
    filterRes.onValueChange = [this] { filterResChanged(); };
    
    filterResValue = filterRes.getValue();
    filterResValue_p = &filterResValue;
    
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Filter", titleArea, Justification::centredTop);
    
    // set the yellow bounds
    Rectangle <float> area (0, 0, 150, 150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
    
    // draw the cutoff word
    Rectangle<int> cutoffArea (20, 128, 40, 20);
    g.setColour(Colours::white);
    g.drawText("Cutoff", cutoffArea, Justification::centred);
    
    // draw resonance word
    Rectangle<int> resArea (90, 128, 40, 20);
    g.setColour(Colours::white);
    g.drawText("Reso", resArea, Justification::centred);
}

void Filter::resized()
{
    
    filterMenu.setBounds (25, 30, 100, 20);
    filterCutoff.setBounds (5, 70, 70, 70);
    filterRes.setBounds (75, 70, 70, 70);

}

void Filter::filterMenuChanged()
{
    switch (filterMenu.getSelectedId()) {
        case 1: filterTypeSelection = 1; break;
        case 2: filterTypeSelection = 2; break;
        case 3: filterTypeSelection = 3; break;
    }
}

void Filter::filterCutoffChanged()
{
    filterCutoffValue = filterCutoff.getValue();
}

void Filter::filterResChanged()
{
    filterResValue = filterRes.getValue();
}
