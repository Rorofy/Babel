/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** PAudio
*/

#include <iostream>
#include "audio/PAudio.hpp"

PAudio::PAudio() : _listening(0), _recording(0)
{
    PaError err = Pa_Initialize();
    int num_dev = Pa_GetDeviceCount();
    std::cout << "PA found:" << num_dev << " devices" << std::endl;

    if (err)
        throw(PAExcept(Pa_GetErrorText(err), 84));
    // input²
    std::cout << "input" << std::endl;
    _inputParam.device = Pa_GetDefaultInputDevice();
    if (_inputParam.device == paNoDevice)
        throw(PAExcept("Error: No default input device.\n", 84));
    _inputParam.channelCount = 2;
    _inputParam.sampleFormat = paFloat32;
    _inputParam.suggestedLatency = Pa_GetDeviceInfo(_inputParam.device)->defaultLowInputLatency;
    _inputParam.hostApiSpecificStreamInfo = NULL;
    std::cout << "output" << std::endl;
    // output
    _outputParam.device = Pa_GetDefaultOutputDevice();
    if (_outputParam.device == paNoDevice)
        throw(PAExcept("Error: No default output device.\n", 84));
    _outputParam.channelCount = 2;
    _outputParam.sampleFormat = paFloat32;
    _outputParam.suggestedLatency = Pa_GetDeviceInfo(_outputParam.device)->defaultLowOutputLatency;
    _outputParam.hostApiSpecificStreamInfo = NULL;
}

PAudio::~PAudio()
{
    Pa_Terminate();
}

float ampSound(float input)
{
    float output, temp;

    if( input < 0.0 ) {
        temp = input + 1.0f;
        output = (temp * temp * temp) - 1.0f;
    } else {
        temp = input - 1.0f;
        output = (temp * temp * temp) + 1.0f;
    }

    return output;
}

static int recordVoiceCB(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    PAudio *audio = static_cast<PAudio *>(userData);
    std::vector<float> tmp;
    const float *in = reinterpret_cast<const float *>(inputBuffer);
    float *out = reinterpret_cast<float *>(outputBuffer);
    float value = 0;
    std::vector<float> &receive = audio->_buf2.getTailElem();


    if(inputBuffer == NULL) {
        for(int i = 0; i < framesPerBuffer; i++) {
            tmp.push_back(0);
            tmp.push_back(0);
        }
    } else {
        for(int i = 0; i < framesPerBuffer; i++) {
            value = *in++;
            tmp.push_back(value);
            value = *in++;
            tmp.push_back(value);
        }
    }
    for(int i = 0; i < framesPerBuffer && i < receive.size(); i++) {
        *out++ = receive[i++];
        if (i >= receive.size()) break;
        *out++ = receive[i];
    }
    audio->getBuffer().insert(tmp);
    audio->_callback();
    return 0;
}

void PAudio::recordVoice(const std::function<void()> &callback)
{
    std::cout << "record" << std::endl;
    PaError err = Pa_OpenStream(&_stream, &_inputParam, NULL, SAMPLE_RATE,
     FRAMES_PER_BUFFER, paClipOff, recordVoiceCB, this);

    if (err)
        throw(PAExcept(Pa_GetErrorText(err), 84));
    err = Pa_StartStream(_stream);
    if (err)
        throw(PAExcept(Pa_GetErrorText(err), 84));
    _recording = 1;
    _callback = callback;
}

void PAudio::stopRecord()
{
    if (!_recording) {
        std::cerr << "Error: Not recording right now" << std::endl;
        return;
    }
    Pa_StopStream(_stream);
}

void PAudio::listenRecord(std::vector<float> &sound)
{
    _buf2.insert(sound);
    _listening = 1;
}

void PAudio::stopListen()
{
    if (!_listening) {
        std::cerr << "Error: Not listening right now" << std::endl;
        return;
    }
}

CircBuffer &PAudio::getBuffer()
{
    return _buf;
}