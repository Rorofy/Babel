/*
** EPITECH PROJECT, 2021
** Untitled (Workspace)
** File description:
** opus
*/

#include <opus.h>
#include <vector>
#include <string>

#define FRAMES_PER_BUFFER 480

#ifndef OPUS_HPP_
#define OPUS_HPP_ 

class Opus
{
    public:
        Opus(/* args */);
        ~Opus();

        std::vector<unsigned char> encode(const std::vector<float> &message);
        std::vector<float> decode(const std::vector<unsigned char> &message, int original_size);

    private:
        OpusEncoder *_encode;
        OpusDecoder *_decode;
        int _error;
};

#endif /* !OPUS_HPP_ */
