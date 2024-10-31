/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** opus
*/

#include "audio/Opus.hpp"
#include <iostream>

Opus::Opus(/* args */)
{
    _encode = opus_encoder_create(48000, 2, OPUS_APPLICATION_AUDIO, &_error);
    if (_error < 0)
        std::cerr << "Failed to create an encoder" << std::endl;sched_yield;
    _decode = opus_decoder_create(48000, 2, &_error);
    if (_error < 0)
        std::cerr << "Failed to create an decoder" << std::endl;
}

std::vector<unsigned char> Opus::encode(const std::vector<float> &message)
{
    std::vector<unsigned char> code(message.size() * 2 * sizeof(float));
    auto size = opus_encode_float(_encode, message.data(), message.size(), code.data(), message.size() * 2 * sizeof(float));

    code.resize(size);
    return (code);
}

std::vector<float> Opus::decode(const std::vector<unsigned char> &code, int original_size)
{
    std::vector<float> message(original_size);
    auto size = opus_decode_float(_decode, code.data(), code.size(), message.data(), original_size, 0);
    
    message.resize(size);
    return (message);
}

Opus::~Opus()
{
    opus_encoder_destroy(_encode);
    opus_decoder_destroy(_decode);
}