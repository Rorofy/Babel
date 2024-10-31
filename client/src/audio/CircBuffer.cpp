/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** CircBuffer
*/

#include "audio/CircBuffer.hpp"

CircBuffer::CircBuffer() : _buf(std::unique_ptr<std::vector<float>[]>(new std::vector<float>[FRAMES_PER_BUFFER])), _head(0), _tail(0), _full(0), _bufSize(FRAMES_PER_BUFFER)
{
}

void CircBuffer::insert(std::vector<float> &val)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _buf[_head] = val;
    if (_full)
        _tail = (_tail + 1) % _bufSize;
    _head = (_head + 1) % _bufSize;
    _full = (_tail == _head);
}

bool CircBuffer::empty()
{
    return (!_full && (_tail == _head));
}

std::vector<float> &CircBuffer::getTailElem()
{
    int tmp = _tail;

    _tail = (_tail + 1) % _bufSize;
    _full = 0;
    return _buf[tmp];
}