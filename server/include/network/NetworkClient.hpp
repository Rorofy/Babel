/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard [WSL: Ubuntu]
** File description:
** NetworkClient
*/

#ifndef NETWORKCLIENT_HPP_
#define NETWORKCLIENT_HPP_

#include <asio.hpp>
#include <memory>

typedef asio::ip::tcp tcp;
typedef asio::io_context io_context;

#include "network/INetwork.hpp"
#include "network/packets/PacketManager.hpp"

class NetworkClient : public INetwork {
    public:
        NetworkClient(io_context &_io_context);
        ~NetworkClient() = default;

        void sendPacket(IPacket &data) override;

        /* Listen the client incoming data and disconnection */
        void listen(PacketManager &manager);

        /* Disconnect the client, is called if the server get the disconnection in middle of receiving data or sending data */
        void disconnect(void);

    public:
        void setUsername(const std::string &username);
        void setIp(const std::string &ip);
        void setToken(const std::string &token);

    public:
        [[nodiscard]] tcp::socket &getSocket();
        [[nodiscard]] const std::string &getUsername();
        [[nodiscard]] const std::string &getToken();
        [[nodiscard]] const std::string &getIp();

    private:
        tcp::socket _socket;
        std::string _ip;
        std::string _token;
        std::string _username;
};

#endif /* !NETWORKCLIENT_HPP_ */