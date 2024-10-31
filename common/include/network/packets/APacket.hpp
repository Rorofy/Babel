/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard [WSL: Ubuntu]
** File description:
** IPacket
*/

#ifndef APACKET_HPP_
#define APACKET_HPP_

#include <memory>
#include <cstring>
#include <iostream>
#include <vector>
#include <array>
#include "network/packets/PacketData.hpp"

class IPacket {
    public:
        IPacket() = default;
        virtual ~IPacket() {};

        virtual void unwrap_data(const std::array<char, 4096> &data, size_t size) = 0;
        virtual void write(void) = 0;
        virtual void read(void) = 0;

        virtual void writeInt(const int value) = 0;
        virtual void writeBool(const bool value) = 0;
        virtual void writeString(const std::string &value) = 0;

        [[nodiscard]] virtual int readInt(void) = 0;
        [[nodiscard]] virtual bool readBool(void) = 0;
        [[nodiscard]] virtual std::string readString(void) = 0;

        [[nodiscard]] virtual PacketDataType &getData(void) = 0;
        [[nodiscard]] virtual size_t getDataSize(void) = 0;
};

class APacket : public IPacket {
    public:
        APacket(int code) : _dIndex(1) {
            writeInt(code);
        }
        virtual ~APacket() {};

        virtual void write(void) = 0;
        virtual void read(void) = 0;

        void unwrap_data(const std::array<char, 4096> &data, size_t size) override {
            auto upcasted = ((int *)data.data());

            for (int i = 1; i < size/4; i++)
                _data.push_back({upcasted[i]});
        }

        void writeInt(const int value) override {
            _data.push_back({value});
        }

        void writeBool(const bool value) override {
            _data.push_back({value});
        }

        void writeString(const std::string &value) override {
            int size = value.size();
            short j = 0;
            PacketDataType typeData;

            for (int i = 0; i < size; i++) {
                typeData.c[j++] = value[i];
                if (j > 3) {
                    _data.push_back(typeData);
                    j = 0;
                }
            }
            typeData.c[j] = '\0';
            _data.push_back(typeData);
        }

        void writeVector(const std::vector<unsigned char> &value) {
            int size = value.size();
            short j = 0;
            PacketDataType typeData;

            for (int i = 0; i < size; i++) {
                typeData.c[j++] = value[i];
                if (j > 3) {
                    _data.push_back(typeData);
                    j = 0;
                }
            }
            typeData.c[j] = '\0';
            _data.push_back(typeData);
        }

        [[nodiscard]] int readInt(void) override {
            if (_dIndex >= _data.size()) return 0;
            return _data[_dIndex++].i;
        }

        [[nodiscard]] bool readBool(void) override {
            if (_dIndex >= _data.size()) return 0;
            return _data[_dIndex++].b;
        }

        [[nodiscard]] std::string readString(void) override {
            std::string str = "";
            PacketDataType typeData;
            char c;

            if (_dIndex >= _data.size()) return "";
            while (_dIndex != _data.size()) {
                typeData = _data[_dIndex++];
                for(int j = 0; j < 4; j++) {
                    c = typeData.c[j];
                    if (c == '\0') return str;
                    str += c;
                }
            }
            return str;
        }

        [[nodiscard]] std::vector<unsigned char> readVector(void) {
            std::vector<unsigned char> str;
            PacketDataType typeData;
            char c;

            if (_dIndex >= _data.size()) return str;
            while (_dIndex != _data.size()) {
                typeData = _data[_dIndex++];
                for(int j = 0; j < 4; j++) {
                    c = typeData.c[j];
                    if (c == '\0') return str;
                    str.push_back(c);
                }
            }
            return str;
        }

        [[nodiscard]] PacketDataType &getData(void) override {
            return *_data.data();
        }

        [[nodiscard]] size_t getDataSize(void) override {
            return _data.size() * sizeof(PacketDataType);
        }

    protected:
        std::vector<union PacketDataType> _data;
        std::size_t _dIndex;
};

#endif /* !APACKET_HPP_ */