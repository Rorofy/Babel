/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Server
*/

#ifndef NETWORKSERVER_HPP_
#define NETWORKSERVER_HPP_

#include <ctime>
#include <iostream>
#include <asio.hpp>
#include <vector>
#include <memory>
#include "network/NetworkClient.hpp"
#include "network/packets/PacketManager.hpp"

typedef asio::io_context io_context;
typedef asio::ip::tcp tcp;

class NetworkServer {
    public:
        NetworkServer();
        ~NetworkServer() = default;

        void start(void);

    private:
        /* Accept new incoming clients connections */
        void handleNewClients(void);

        NetworkClient &getNetwork(const std::string &token);
        NetworkClient &getNetworkFromName(const std::string &name);
        bool userInSession(const std::string &token);
        bool userInSessionFromName(const std::string &name);

    private:
        io_context _io_context;
        tcp::acceptor _acceptor;
        std::unordered_map<std::string, std::shared_ptr<NetworkClient>> _sessionTokens;
        std::unordered_map<std::string, std::shared_ptr<NetworkClient>> _userSessionTokens;
        PacketManager _packetManager;
};

#endif /* !NETWORKSERVER_HPP_ */