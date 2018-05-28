/*
  ==============================================================================

    Envelope.cpp
    Created: 25 May 2018 8:31:36am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope()
{
    setSize(200, 200);
    
    //slider initialization values
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    attackSlider.onValueChange = [this] { attackChanged(); };
    addAndMakeVisible(&attackSlider);
    
    decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(1.0f, 2000.0f);
    decaySlider.setValue(1.0f);
    decaySlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    decaySlider.onValueChange = [this] { decayChanged(); };
    addAndMakeVisible(&decaySlider);
    
    sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.8f);
    sustainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    sustainSlider.onValueChange = [this] { sustainChanged(); };
    addAndMakeVisible(&sustainSlider);
    
    releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.8f);
    releaseSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    releaseSlider.onValueChange = [this] { releaseChanged(); };
    addAndMakeVisible(&releaseSlider);
    
    //sends value of the sliders to the tree state in the processor
    attackVal = attackSlider.getValue();
    decayVal = decaySlider.getValue();
    sustainVal = sustainSlider.getValue();
    releaseVal = releaseSlider.getValue();
    
    // Set pointer to values
    attackVal_P = &attackVal;
    decayVal_P = &decayVal;
    sustainVal_P = &sustainVal;
    releaseVal_P = &releaseVal;
}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{
    //fancy stuff for the UI background etc
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Envelope", titleArea, Justification::centredTop);
    
    //static positioning for now due to time, make dynamic later
    g.drawText ("A", 32, 120, 20, 20, Justification::centredTop);
    g.drawText ("D", 55, 120, 20, 20, Justification::centredTop);
    g.drawText ("S", 78, 120, 20, 20, Justification::centredTop);
    g.drawText ("R", 100, 120, 20, 20, Justification::centredTop);
    
    Rectangle <float> area (0, 0, 150, 150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    //draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
    Rectangle<int> area = getLocalBounds().reduced(30);
    
    int sliderWidth = 23;
    int sliderHeight = 175;
    
    //draw sliders by reducing area from rectangle above
    attackSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds (area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}

void Envelope::attackChanged()
{
    attackVal = attackSlider.getValue();
}

void Envelope::decayChanged()
{
    decayVal = decaySlider.getValue();
}

void Envelope::sustainChanged()
{
    sustainVal = sustainSlider.getValue();
}

void Envelope::releaseChanged()
{
    releaseVal = releaseSlider.getValue();
}
