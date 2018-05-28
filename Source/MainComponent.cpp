/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : synthAudioSource(keyboardState, envGui, oscGui, filterGui),
keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(keyboardComponent);
    
    addAndMakeVisible(midiInputListLabel);
    midiInputListLabel.setText("Midi Input", dontSendNotification);
    midiInputListLabel.attachToComponent(&midiInputList, true);
    
    addAndMakeVisible(midiInputList);
    midiInputList.setTextWhenNoChoicesAvailable("No MIDI Inputs Enabled");
    auto midiInputs = MidiInput::getDevices();
    midiInputList.addItemList(midiInputs, 1);
    midiInputList.onChange = [this] { setMidiInput (midiInputList.getSelectedItemIndex()); };
    
    for (auto midiInput : midiInputs)
    {
        if (deviceManager.isMidiInputEnabled(midiInput))
        {
            setMidiInput (midiInputs.indexOf(midiInput));
            break;
        }
    }
    
    if (midiInputList.getSelectedId() == 0)
        setMidiInput (0);
    
    setAudioChannels (0, 2);
    
    setSize (800, 600);
    startTimer(400);
    
    // Add OSC
    addAndMakeVisible(oscGui);
    
    // Add ENV
    addAndMakeVisible(envGui);
    
    // Add FIL
    addAndMakeVisible(filterGui);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    synthAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    synthAudioSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    synthAudioSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    midiInputList.setBounds(200, 10, getWidth() - 210, 20);
    keyboardComponent.setBounds(10, 190, getWidth() - 20, getHeight() - 200);
    
    // Oscillator
    Rectangle<int> area2 (35, 35, 150, 150);
    oscGui.setBounds(area2);
    
    // Envelope
    Rectangle<int> area3 (210, 35, 150, 150);
    envGui.setBounds(area3);
    
    // Filter
    Rectangle<int> area4 (385, 35, 150, 150);
    filterGui.setBounds(area4);
}

void MainComponent::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}

void MainComponent::setMidiInput(int index)
{
    auto list = MidiInput::getDevices();
    
    deviceManager.removeMidiInputCallback(list[lastInputIndex], synthAudioSource.getMidiCollector());
    
    auto newInput = list[index];
    
    if (! deviceManager.isMidiInputEnabled(newInput))
        deviceManager.setMidiInputEnabled(newInput, true);
    
    deviceManager.addMidiInputCallback(newInput, synthAudioSource.getMidiCollector());
    midiInputList.setSelectedId(index + 1, dontSendNotification);
    
    lastInputIndex = index;
}

void MainComponent::comboBoxChanged(ComboBox* box)
{
    
}
