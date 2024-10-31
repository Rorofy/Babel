/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Audio
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include <QMetaType>
#include <QObject>
#include "audio/PAudio.hpp"
#include "audio/Opus.hpp"

class Audio : public QObject {
    Q_OBJECT

    public:
        Audio() = default;
        ~Audio() = default;

        void startRecord(void);

    signals:
        void recordReady(const std::string &string);

    public slots:
        void playSound(const std::string &sound);

    private:
        void recordCallback();

    private:
        PAudio _audio;
        Opus _opus;
};

#endif /* !AUDIO_HPP_ */
