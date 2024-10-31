/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard [WSL: Ubuntu]
** File description:
** PacketManager
*/

#include "network/packets/PacketManager.hpp"

static void getHeaderCode(const std::string &data)
{
}

void PacketManager::buildPacketFromData(INetwork &sender, const std::array<char, 4096> &data, std::size_t size)
{
    PacketDataType code;
    std::unique_ptr<IPacket> packet;

    std::memcpy(&code, data.data(), sizeof(PacketDataType));
    if (_packetFactories.count(code.i) == 0) return;
    packet = _packetFactories[code.i]->build(data, size);
    packet->read();
    packetCall(sender, code.i, *packet);
}

void PacketManager::packetCall(INetwork &sender, const int code, IPacket &packet)
{
    _packetCallbacks[code](sender, packet);
}