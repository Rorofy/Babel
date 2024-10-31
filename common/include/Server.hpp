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
        const std::string &createSessionToken(const std::string &name);
        const std::string &getUser(const std::string &token);
        bool userInSession(const std::string &token);

    private:
        std::unique_ptr<IDataBase> _db;
        NetworkServer _network;
        std::unordered_map<std::string, std::string> _sessionTokens;
        std::unordered_map<std::string, std::string> _userSessionTokens;
};

#endif /* !SERVER_HPP_ */