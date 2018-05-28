/*
  ==============================================================================

    Oscillator.cpp
    Created: 25 May 2018 8:31:12am
    Author:  Odniel Gonzalez

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

Oscillator::Oscillator()
{
    setSize(200, 200);
    addAndMakeVisible(&oscMenu);
    
    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    oscMenu.addItem("Triangle", 4);
    oscMenu.setJustificationType(Justification::centred);
    oscMenu.onChange = [this] { oscMenuChanged(); };
    oscMenu.setSelectedId (1);
    
    waveSelection = 1;
    waveSelection_P = &waveSelection;
    
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    //background stuff
    Rectangle<int> titleArea (0, 10, getWidth(), 20);
    
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawText("Osc", titleArea, Justification::centredTop);
    
    
    Rectangle <float> area (0, 0, 150, 150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Oscillator::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(30);
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(ComboBox* box)
{
    
}

void Oscillator::oscMenuChanged()
{
    switch (oscMenu.getSelectedId())
    {
        case 1: waveSelection = 1; break;
        case 2: waveSelection = 2; break;
        case 3: waveSelection = 3; break;
        case 4: waveSelection = 4; break;
    }
}
