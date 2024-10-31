/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** PAudio
*/

#ifndef PAUDIO_HPP_
#define PAUDIO_HPP_

#include <vector>
#include <functional>
#include "portaudio.h"
#include "PAExcept.hpp"
#include "CircBuffer.hpp"

#define SAMPLE_RATE 48000
#define FRAMES_PER_BUFFER 480

class PAudio {
    public:
        PAudio();
        ~PAudio();

        void recordVoice(const std::function<void()> &callback);
        void stopRecord();
        void listenRecord(std::vector<float> &voice);
        void stopListen();
        [[nodiscard]] CircBuffer &getBuffer();

    public:
        std::function<void()> _callback;
        CircBuffer _buf;

        bool _listening;
        bool _recording;

        PaStream *_stream;
        PaStreamParameters _inputParam;
        PaStreamParameters _outputParam;
        CircBuffer _buf2;
    private:
};

#endif /* !PAUDIO_HPP_ */
