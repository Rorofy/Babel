/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard [WSL: Ubuntu]
** File description:
** IPacketFactory
*/

#ifndef PACKETFACTORY_HPP_
#define PACKETFACTORY_HPP_

#include <memory>
#include "network/packets/APacket.hpp"

class IPacketFactory
{
    public:
        IPacketFactory() = default;
        virtual ~IPacketFactory() {};

        virtual std::unique_ptr<IPacket> build(const std::array<char, 4096> &data, std::size_t size) = 0;
};

template<typename T>
class PacketFactory : public IPacketFactory {
    public:
        PacketFactory() = default;
        ~PacketFactory() = default;

        std::unique_ptr<IPacket> build(const std::array<char, 4096> &data, std::size_t size) override {
            std::unique_ptr<IPacket> packet = std::make_unique<T>();

            packet->unwrap_data(data, size);
            return std::move(packet);
        }
};

#endif /* !PACKETFACTORY_HPP_ */
