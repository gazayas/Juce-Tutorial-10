// https://www.youtube.com/watch?v=GjNeYI6-uNE&list=PLLgJJsrdwhPxa6-02-CeHW8ocwSwl2jnu&index=11
// The bulk of the code is under MainComponent::getNextAudioBlock

/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
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
}

// AudioSourceChannelInfo seems to be a class where we can get information about a buffer
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // -> has to be used on buffer because buffer is a pointer
    for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
    {
        // point into address of buffer to work with value
        // startSample goes to first index of buffer
        float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        
        // write random values into buffer
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            // The random numbers are supposed to produce white noise.
            // The equation yields values of -0.25 ~ +0.25 random was declared in header.
            // Without the * 0.25, it would be -1.0 ~ 1.0, but apparently
            // that's too loud for the speakers.
            buffer[sample] = (random.nextFloat() * 2.0f - 1.0f) * 0.25f;
        }
    }
    // This was originally here, but had to comment it out for the code to work.
    // bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
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
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
