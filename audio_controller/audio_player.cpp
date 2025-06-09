/*
 * audio_player.cpp
 *
 *  Created on: Jan 8, 2024
 *      Author: bekdouche
 */

#include "audio_player.h"

AudioManager::AudioManager() : currentBackground(nullptr), currentEffect(nullptr) {
    Pa_Initialize();
}

AudioManager::~AudioManager() {
    Pa_Terminate();
    for (auto &pair : audioFiles) {
        sf_close(pair.second.file);
    }
}

bool AudioManager::loadAudioFile(float volume, const std::string &name, const char *filename) {
    AudioData data;
    data.file = sf_open(filename, SFM_READ, &data.info);
    if (!data.file) {
        std::cerr << "Could not open audio file: " << filename << std::endl;
        return false;
    }
    data.volume = volume; // Default volume
    audioFiles[name] = data;
    return true;
}

void AudioManager::playBackground(const std::string &name) {
    if (audioFiles.find(name) != audioFiles.end()) {
        currentBackground = &audioFiles[name];
        sf_seek(currentBackground->file, 0, SEEK_SET); // Rewind to start
        Pa_OpenDefaultStream(&backgroundStream, 0, currentBackground->info.channels, paFloat32, currentBackground->info.samplerate, 256, paBackgroundCallback, currentBackground);
        Pa_StartStream(backgroundStream);
    }
}

void AudioManager::playEffect(const std::string &name) {
    if (audioFiles.find(name) != audioFiles.end()) {
        currentEffect = &audioFiles[name];
        sf_seek(currentEffect->file, 0, SEEK_SET); // Rewind to start
        Pa_OpenDefaultStream(&effectStream, 0, currentEffect->info.channels, paFloat32, currentEffect->info.samplerate, 256, paEffectCallback, currentEffect);
        Pa_StartStream(effectStream);
    }
}

void AudioManager::stopBackground() {
    if (backgroundStream) {
        Pa_StopStream(backgroundStream);
        Pa_CloseStream(backgroundStream);
        backgroundStream = nullptr;
    }
}

void AudioManager::update() {
    if (backgroundStream && !Pa_IsStreamActive(backgroundStream)) {
        playBackground("background"); // Restart background music if needed
    }
    if (effectStream && !Pa_IsStreamActive(effectStream)) {
        Pa_StopStream(effectStream);
        Pa_CloseStream(effectStream);
        effectStream = nullptr;
    }
}

void AudioManager::setVolume(float volume) {
    if (currentBackground) {
        currentBackground->volume = volume;
    }
    if (currentEffect) {
        currentEffect->volume = volume;
    }
}

int AudioManager::paBackgroundCallback(const void *inputBuffer, void *outputBuffer,
                                       unsigned long framesPerBuffer,
                                       const PaStreamCallbackTimeInfo* timeInfo,
                                       PaStreamCallbackFlags statusFlags,
                                       void *userData) {
    AudioData *data = (AudioData*)userData;
    float *out = (float*)outputBuffer;
    sf_count_t framesRead = sf_readf_float(data->file, out, framesPerBuffer);
    if (framesRead < framesPerBuffer) {
        sf_seek(data->file, 0, SEEK_SET);
        framesRead += sf_readf_float(data->file, out + framesRead, framesPerBuffer - framesRead);
    }
    for (sf_count_t i = 0; i < framesRead * data->info.channels; i++) {
        out[i] *= data->volume;
    }
    return paContinue;
}

int AudioManager::paEffectCallback(const void *inputBuffer, void *outputBuffer,
                                   unsigned long framesPerBuffer,
                                   const PaStreamCallbackTimeInfo* timeInfo,
                                   PaStreamCallbackFlags statusFlags,
                                   void *userData) {
    AudioData *data = (AudioData*)userData;
    float *out = (float*)outputBuffer;
    sf_count_t framesRead = sf_readf_float(data->file, out, framesPerBuffer);
    for (sf_count_t i = 0; i < framesRead * data->info.channels; i++) {
        out[i] *= data->volume;
    }
    return (framesRead < framesPerBuffer) ? paComplete : paContinue;
}
