/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** CircBuffer
*/

#ifndef CIRCBUFFER_HPP_
#define CIRCBUFFER_HPP_

#include <memory>
#include <mutex>
#include <vector>

#define FRAMES_PER_BUFFER 480

class CircBuffer {
    public:
        CircBuffer();
        ~CircBuffer() = default;

        void insert(std::vector<float> &val);
        [[nodiscard]] std::vector<float> &getTailElem();
        [[nodiscard]] bool empty();

    private:
        std::unique_ptr<std::vector<float>[]> _buf;
        std::mutex _mutex;
        int _bufSize;
        int _head;
        int _tail;
        bool _full;
};

#endif /* !CIRCBUFFER_HPP_ */
