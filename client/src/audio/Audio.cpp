/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Audio
*/

#include "audio/Audio.hpp"

void Audio::startRecord()
{
    _audio.recordVoice([this] {
        recordCallback();
    });
}

void Audio::recordCallback()
{
    auto &sound = _audio.getBuffer().getTailElem();

    if (sound.empty()) return;
    auto data = _opus.encode(sound);
    std::string str(data.begin(), data.end());
    emit recordReady(str);
}

void Audio::playSound(const std::string &sound)
{
    std::vector<unsigned char> data(sound.begin(), sound.end());
    std::vector<float> decoded = _opus.decode(data, data.size());

    _audio.listenRecord(decoded);
}

#include "audio/moc_Audio.cpp"