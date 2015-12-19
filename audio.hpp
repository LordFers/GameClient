#ifndef _H_AUDIO_
#define _H_AUDIO_

#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

class cAudio{
    public:
        cAudio();
        void PlayMIDI(std::string);
        void PlayWav(std::string);
        bool midi_run;
        bool wave_run;
        float counter;

        sf::Music music;
        sf::SoundBuffer soundbuffer;
        int lastwave;
};

#endif // _H_AUDIO_
