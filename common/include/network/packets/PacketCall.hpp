/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** PacketCall
*/

#ifndef PACKETCALL_HPP_
#define PACKETCALL_HPP_

#include <vector>
#include "network/Protocol.hpp"
#include "network/packets/APacket.hpp"

class PacketCall : public APacket {
    public:
        PacketCall(const std::vector<std::string> &callers = {}) : APacket(PACKET_CALL),
            _callers(callers) {};
        ~PacketCall() {};

        void write(void) override {
            writeInt(_callers.size());
            for (auto &x : _callers)
                writeString(x);
        }

        void read(void) override {
            int count = readInt();

            for (int i = 0; i < count; i++)
                _callers.push_back(readString());
        }

        [[nodiscard]] std::vector<std::string> getCallers() {return _callers;};

    private:
        std::vector<std::string> _callers;
};

class PacketCallRequest : public APacket {
    public:
        PacketCallRequest() : APacket(PACKET_CALL_REQUEST) {};
        PacketCallRequest(const std::vector<std::string> &ips) :
            _ips(ips), APacket(PACKET_CALL_REQUEST) {};        
        ~PacketCallRequest() {};

        void write(void) override {
            writeInt(_ips.size());
            for (auto &x : _ips)
                writeString(x);
        }

        void read(void) override {
            int count = readInt();

            for (int i = 0; i < count; i++)
                _ips.push_back(readString());
        }

        [[nodiscard]] std::vector<std::string> getCallers() {return _ips;};

    private:
        std::vector<std::string> _ips;
};


class PacketCallData : public APacket {
    public:
        PacketCallData(const std::string &sound = "") :
            APacket(PACKET_CALL_DATA), _sound(sound) {};
        ~PacketCallData() {};

        void write(void) override {
            writeString(_sound);
        }

        void read(void) override {
            _sound = readString();
        }

        const std::string getSound(void) {return _sound;};
    private:
        std::string _sound;
};

#endif /* !PACKETCALL_HPP_ */