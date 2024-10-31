/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <memory>
#include <unordered_map>
#include <vector>
#include "network/NetworkServer.hpp"
#include "db/IDataBase.hpp"

class Server {
    public:
        Server();
        ~Server() = default;

        void start(void);
    
    public:
        IDataBase &getDB(void);

        [[nodiscard]] static Server &provide(void);
        static const std::string createSessionToken(const std::string &ip);

    private:
        std::unique_ptr<IDataBase> _db;
        NetworkServer _network;
};

#endif /* !SERVER_HPP_ */