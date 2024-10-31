/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Server
*/

#include <sstream>
#include "Server.hpp"
#include "db/SQLite.hpp"

Server::Server()
{
    _db = std::make_unique<SQLite>();
}

void Server::start()
{
    _network.start();
}

IDataBase &Server::getDB(void)
{
    return *_db;
}

Server &Server::provide(void) {
    static Server instance;

    return instance;
}

const std::string Server::createSessionToken(const std::string &ip)
{
    std::stringstream ss;

    srand(time(NULL) + rand());
    for(int i = 0;i < 64;i++) {
        int j = rand() % 127;
        while(j < 32)
                j = rand() % 127;
        ss << char(j);
    }
    return ss.str();
}