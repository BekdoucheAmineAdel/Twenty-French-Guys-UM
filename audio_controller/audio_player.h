/*
 * audio_player.h
 *
 *  Created on: Jan 8, 2024
 *      Author: bekdouche
 */

#ifndef AUDIO_CONTROLLER_AUDIO_PLAYER_H_
#define AUDIO_CONTROLLER_AUDIO_PLAYER_H_

// Includes
#include <portaudio.h>
#include <sndfile.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>

typedef struct {
    SNDFILE *file;
    SF_INFO info;
    float volume;
} AudioData;

class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    bool loadAudioFile(float volume, const std::string &name, const char *filename);
    void playBackground(const std::string &name);
    void playEffect(const std::string &name);
    void stopBackground();
    void update();
    void setVolume(float volume);

private:
    static int paBackgroundCallback(const void *inputBuffer, void *outputBuffer,
                                    unsigned long framesPerBuffer,
                                    const PaStreamCallbackTimeInfo* timeInfo,
                                    PaStreamCallbackFlags statusFlags,
                                    void *userData);
    static int paEffectCallback(const void *inputBuffer, void *outputBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeInfo,
                                PaStreamCallbackFlags statusFlags,
                                void *userData);
    PaStream *backgroundStream;
    PaStream *effectStream;
    std::map<std::string, AudioData> audioFiles;
    AudioData *currentBackground;
    AudioData *currentEffect;
};

extern AudioManager audioManager;

#endif /* AUDIO_CONTROLLER_AUDIO_PLAYER_H_ */
