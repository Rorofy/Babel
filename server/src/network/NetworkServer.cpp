/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** NetworkServer
*/

#include <functional>
#include "Server.hpp"
#include "network/Protocol.hpp"
#include "network/packets/PacketAuth.hpp"
#include "network/packets/PacketCall.hpp"
#include "network/packets/PacketFriend.hpp"

NetworkServer::NetworkServer() :
    _acceptor(_io_context, tcp::endpoint(asio::ip::tcp::v4(), 6666))
{
    _packetManager.registerPacket<PacketLogin>(PACKET_LOGIN, [this] (INetwork &network, IPacket &packet){
        auto &server = Server::provide();
        PacketLogin login = ((PacketLogin &)packet);
        const std::string &username = login.getUsername();

        if (userInSession(login.getToken()) && !userInSessionFromName(username)
            && server.getDB().userExist(username) && server.getDB().userPassword(username, login.getPassword())) {
            PacketLoginAnswer answer(true);

            _userSessionTokens[username] = _sessionTokens[login.getToken()];
            ((NetworkClient &)network).setUsername(username);
            std::cout << "User " << username << " logged" << std::endl;
            network.sendPacket(answer);
        } else {
            PacketLoginAnswer answer(false);
            network.sendPacket(answer);
        }
    });
    _packetManager.registerPacket<PacketRegister>(PACKET_REGISTER, [] (INetwork &network, IPacket &packet){
        auto &server = Server::provide();
        PacketRegister login = ((PacketRegister &)packet);
        auto &username = login.getUsername();

        if (!username.empty() && username.find_first_not_of(' ') != std::string::npos && !server.getDB().userExist(username)) {
            PacketRegisterAnswer answer(true);

            std::cout << "new user register, username: " << username << std::endl;
            server.getDB().userAdd(username, login.getPassword());
            network.sendPacket(answer);
        } else {
            PacketRegisterAnswer answer(false);
            network.sendPacket(answer);
        }
    });
    _packetManager.registerPacket<PacketCall>(PACKET_CALL, [this] (INetwork &network, IPacket &packet){
        std::vector<std::string> ips;

        for (auto &peer : ((PacketCall&)packet).getCallers())
            if (userInSessionFromName(peer))
                ips.push_back(getNetworkFromName(peer).getIp());
        PacketCallRequest request(ips);

        for (auto &peer : ((PacketCall&)packet).getCallers())
            getNetworkFromName(peer).sendPacket(request);
    });
    _packetManager.registerPacket<PacketFriendAdd>(PACKET_FRIEND_ADD, [this] (INetwork &network, IPacket &packet){
        auto &pack = (PacketFriendAdd&) packet;
        auto &client = (NetworkClient &)network;
        auto &db = Server::provide().getDB();

        if (!userInSession(pack.getToken()) || !db.userExist(pack.getFriend()) || pack.getFriend() == client.getUsername() ||
            db.userHaveFriend(client.getUsername(), pack.getFriend(), 0) || db.userHaveFriend(client.getUsername(), pack.getFriend(), 1)) {
            PacketFriendAddAnswer answer(pack.getFriend(), false);

            network.sendPacket(answer);
        } else if (db.userHaveFriend(pack.getFriend(), client.getUsername(), 1)) {
            PacketFriendAddAnswer answer(pack.getFriend(), true);

            network.sendPacket(answer);
            if (userInSessionFromName(pack.getFriend())) {
                PacketFriendAddAnswer answer2(client.getUsername(), true);

                getNetworkFromName(pack.getFriend()).sendPacket(answer2);
            }
            db.userAddFriend(pack.getFriend(), client.getUsername());
        } else if (userInSessionFromName(pack.getFriend())) {
            PacketFriendRequest request(client.getUsername());

            Server::provide().getDB().userAddFriendRequest(client.getUsername(), pack.getFriend());
            getNetworkFromName(pack.getFriend()).sendPacket(request);
        }
    });
    _packetManager.registerPacket<PacketFriendRequestAnswer>(PACKET_FRIEND_REQUEST_ANSWER, [this] (INetwork &network, IPacket &packet){
        auto &pack = ((PacketFriendRequestAnswer&)packet);
        auto &db = Server::provide().getDB();
        auto &username = ((NetworkClient &)network).getUsername();

        if (!userInSession(pack.getToken()) || !db.userHaveFriend(pack.getUser(), username, 1)) return;
        if (pack.getAnswer())
            db.userAddFriend(pack.getUser(), username);
        else
            db.userRemoveFriendRequest(pack.getUser(), username);
        if (userInSessionFromName(pack.getUser())) {
            PacketFriendAddAnswer answer(username, pack.getAnswer());

            getNetworkFromName(pack.getUser()).sendPacket(answer);
        }
    });
    _packetManager.registerPacket<PacketFriendsGet>(PACKET_FRIENDS_GET, [this] (INetwork &network, IPacket &packet){
        auto &token = ((PacketFriendsGet &)packet).getToken();
        auto &client = (NetworkClient &)network;

        if (userInSession(token)) {
            PacketFriendsGetAnswer answer(Server::provide().getDB().getUserFriends(client.getUsername()));

            network.sendPacket(answer);
        } else {
            PacketFriendsGetAnswer empty;
            network.sendPacket(empty);
        }
    });
}

void NetworkServer::handleNewClients(void)
{
    auto client = std::make_shared<NetworkClient>(_io_context);

    _acceptor.async_accept(client->getSocket(), [this, client] (const asio::system_error &error) {
        auto ip = client->getSocket().remote_endpoint().address().to_string();
        auto token = Server::createSessionToken(ip);
        PacketToken packet(token);

        client->setIp(ip);
        client->setToken(token);
        std::cout << "New Connection Accepted: " << std::endl << "Ip: " << ip << std::endl << "Token: " << token << std::endl;
        this->_sessionTokens[token] = client;
        client->listen(_packetManager);
        client->sendPacket(packet);
        this->handleNewClients();
    });
}

void NetworkServer::start()
{
    handleNewClients();
    _io_context.run();
    while (true) {
        
    }
}

NetworkClient &NetworkServer::getNetwork(const std::string &token)
{
    return *_sessionTokens[token];
}

NetworkClient &NetworkServer::getNetworkFromName(const std::string &name)
{
    return *_userSessionTokens[name];
}

bool NetworkServer::userInSession(const std::string &token)
{
    return _sessionTokens.count(token) != 0;
}

bool NetworkServer::userInSessionFromName(const std::string &token)
{
    return _userSessionTokens.count(token) != 0;
}