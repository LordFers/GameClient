#include "audio.hpp"
class cSound : public sf::SoundStream
{
public:

    void load(const sf::SoundBuffer& buffer)
    {
        // extract the audio samples from the sound buffer to our own container
        m_samples.assign(buffer.getSamples(), buffer.getSamples() + buffer.getSampleCount());

        // reset the current playing position
        m_currentSample = 0;

        // initialize the base class
        initialize(buffer.getChannelCount(), buffer.getSampleRate());
    }

private:

    virtual bool onGetData(Chunk& data)
    {
        // number of samples to stream every time the function is called;
        // in a more robust implementation, it should be a fixed
        // amount of time rather than an arbitrary number of samples
        const int samplesToStream = 50000;

        // set the pointer to the next audio samples to be played
        data.samples = &m_samples[m_currentSample];

        // have we reached the end of the sound?
        if (m_currentSample + samplesToStream <= m_samples.size())
        {
            // end not reached: stream the samples and continue
            data.sampleCount = samplesToStream;
            m_currentSample += samplesToStream;
            return true;
        }
        else
        {
            // end of stream reached: stream the remaining samples and stop playback
            data.sampleCount = m_samples.size() - m_currentSample;
            m_currentSample = m_samples.size();
            return false;
        }
    }

    virtual void onSeek(sf::Time timeOffset)
    {
        // compute the corresponding sample index according to the sample rate and channel count
        m_currentSample = static_cast<std::size_t>(timeOffset.asSeconds() * getSampleRate() * getChannelCount());
    }

    std::vector<sf::Int16> m_samples;
    std::size_t m_currentSample;
};

cSound sound[30];

cAudio::cAudio()
{
    lastwave = 0;
    midi_run = false;
    wave_run = false;
}

void cAudio::PlayMIDI(std::string filename)
{
    music.stop();
    // Declare a new music
    // Open it from an audio file
    if (!music.openFromFile(filename))
    {
        std::cout << "Error loading file: " << filename << std::endl;
    }

    // Change some parameters
    music.setPosition(0, 0, 0); // change its 3D position
    music.setPitch(1);           // increase the pitch
    music.setVolume(50);         // reduce the volume
    music.setLoop(true);         // make it loop
    // Play it
    music.play();
    midi_run = true;
}

void cAudio::PlayWav(std::string filename)
{
    if (lastwave >= 30) lastwave = 0;
    soundbuffer.loadFromFile(filename);
    sound[lastwave].load(soundbuffer);
    sound[lastwave].play();
    lastwave++;

    wave_run = true;
}
