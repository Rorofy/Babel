/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** NetworkClient
*/

#include <iostream>
#include "network/NetworkClient.hpp"

NetworkClient::NetworkClient(io_context &_io_context) :
    _socket(_io_context)
{
}

void NetworkClient::sendPacket(IPacket &packet)
{
    packet.write();
    _socket.send(asio::buffer(&packet.getData(), packet.getDataSize()));
}

void NetworkClient::listen(PacketManager &manager)
{
    std::array<char, 4096> data = {'\0'};

    _socket.async_receive(asio::buffer(data), [this, &data, &manager](const asio::error_code &error, std::size_t size) {
        if (error == asio::error::eof) // Connection closed cleanly by peer.
            return;
        if (size >= sizeof(int))
            manager.buildPacketFromData(*this, data, size);
        this->listen(manager);
    });
}

void NetworkClient::disconnect(void)
{
}

void NetworkClient::setUsername(const std::string &username)
{
    _username = username;
}

void NetworkClient::setIp(const std::string &ip)
{
    _ip = ip;
}

void NetworkClient::setToken(const std::string &token)
{
    _token = token;
}

tcp::socket &NetworkClient::getSocket(void)
{
    return _socket;
}

const std::string &NetworkClient::getUsername()
{
    return _username;
}

const std::string &NetworkClient::getToken()
{
    return _token;
}

const std::string &NetworkClient::getIp()
{
    return _ip;
}