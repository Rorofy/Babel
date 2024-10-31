/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard [WSL: Ubuntu]
** File description:
** PacketManager
*/

#ifndef PACKETMANAGER_HPP_
#define PACKETMANAGER_HPP_

#include <functional>
#include <unordered_map>
#include "network/INetwork.hpp"
#include "network/packets/APacket.hpp"
#include "network/packets/PacketFactory.hpp"

typedef std::function<void (INetwork &network, IPacket &packet)> packetCallback;

class PacketManager {
    public:
        PacketManager() = default;
        ~PacketManager() = default;

        template<typename T>
        void registerPacket(int code, packetCallback callback) {
            _packetFactories[code] = std::make_unique<PacketFactory<T>>();
            _packetCallbacks[code] = callback;
        }

        void buildPacketFromData(INetwork &sender, const std::array<char, 4096> &data, std::size_t size);
        void packetCall(INetwork &sender, const int code, IPacket &packet);

    private:
        std::unordered_map<int, packetCallback> _packetCallbacks;
        std::unordered_map<int, std::unique_ptr<IPacketFactory>> _packetFactories;
};

#endif /* !PACKETMANAGER_HPP_ */