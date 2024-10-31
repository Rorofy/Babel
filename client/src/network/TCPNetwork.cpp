/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** TCPNetwork
*/

#include "Client.hpp"
#include "network/TCPNetwork.hpp"
#include "network/Protocol.hpp"
#include "network/packets/PacketAuth.hpp"
#include "network/packets/PacketFriend.hpp"
#include "network/packets/PacketCall.hpp"


TCPNetwork::TCPNetwork() :
    _socket(new QTcpSocket(0))
{
    initCallbacks();
    _packetManager.registerPacket<PacketToken>(PACKET_TOKEN, [this] (INetwork &sender, IPacket &packet) {        
        this->_token = ((PacketToken &)packet).getToken();
        std::cout << "Session Token: " <<  _token << std::endl;
    });
    _packetManager.registerPacket<PacketLoginAnswer>(PACKET_LOGIN_ANSWER, [this] (INetwork &sender, IPacket &packet) {
        PacketFriendsGet friends(_token);
        PacketLoginAnswer &answer = (PacketLoginAnswer &)packet;

        if (answer.accepted()) {
            sendPacket(friends);
            emit loginAccepted();
            std::cout << "Login accepted" << std::endl;
        }
        else
            std::cout << "Login refused" << std::endl;

    });
    _packetManager.registerPacket<PacketRegisterAnswer>(PACKET_REGISTER_ANSWER, [this] (INetwork &sender, IPacket &packet){
        PacketRegisterAnswer &answer = (PacketRegisterAnswer &)packet;

        if (answer.accepted()) {
            emit registerAccepted();
            std::cout << "Register accepted" << std::endl;
        }
        else
            std::cout << "Register refused" << std::endl;

    });
    _packetManager.registerPacket<PacketCallRequest>(PACKET_CALL_REQUEST, [this] (INetwork &sender, IPacket &packet){
        emit receiveCall(((PacketCallRequest &)packet).getCallers());
    });
    _packetManager.registerPacket<PacketFriendRequest>(PACKET_FRIEND_REQUEST, [this] (INetwork &sender, IPacket &packet){
        emit friendRequest(((PacketFriendRequest&)packet).getUser());
    });
    _packetManager.registerPacket<PacketFriendAddAnswer>(PACKET_FRIEND_ADD_ANSWER, [this] (INetwork &sender, IPacket &packet){
        auto &pack = ((PacketFriendAddAnswer&)packet);
        if (pack.getAnswer()) {
            emit newFriend(pack.getUser());
            std::cout << pack.getUser() << ": Friend Request Accepted" << std::endl;
        } else
            std::cout << pack.getUser() << ": Friend Request Declined by the user or server" << std::endl;
    });
    _packetManager.registerPacket<PacketFriendsGetAnswer>(PACKET_FRIENDS_GET_ANSWER, [this] (INetwork &sender, IPacket &packet){
        emit friendUpdate(((PacketFriendsGetAnswer &)packet).getFriends());
    });
}

void TCPNetwork::initCallbacks()
{
    connect(_socket, &QAbstractSocket::connected, this, &TCPNetwork::connectHandler);
    connect(_socket, &QAbstractSocket::disconnected, this, &TCPNetwork::disconnected);
    connect(_socket, &QIODevice::readyRead, this, &TCPNetwork::readData);
    connect(_socket, &QAbstractSocket::errorOccurred, this, &TCPNetwork::handleErrors);
}

void TCPNetwork::connectTo(const std::string &host, int port)
{
    _socket->connectToHost(QString::fromStdString(host), 6666);
}

void TCPNetwork::connectHandler()
{
    std::cout << "Connected:" << std::endl;
}

void TCPNetwork::disconnect()
{
    std::cout << "Disconnected !" << std::endl;
    emit disconnected();
}

void TCPNetwork::addFriend(const std::string &username)
{
    PacketFriendAdd packet(_token, username);

    sendPacket(packet);
}

void TCPNetwork::login(const std::string &username, const std::string &password)
{
    PacketLogin packet(_token, username, password);

    sendPacket(packet);
}

void TCPNetwork::registerStart(const std::string &username, const std::string &password)
{
    PacketRegister packet(username, password);

    sendPacket(packet);
}

void TCPNetwork::startCall(const std::vector<std::string> &peers)
{
    PacketCall packet(peers);

    sendPacket(packet);
}

void TCPNetwork::answerRequest(const std::string &username, bool answer)
{
    PacketFriendRequestAnswer packet(_token, username, answer);

    emit newFriend(username);
    sendPacket(packet);
}

void TCPNetwork::readData()
{
    _buffer.fill('\0');
    _bufferSize = _socket->read(_buffer.data(), 4096);
    if ((int)_bufferSize == -1)
        return;
    _packetManager.buildPacketFromData(*this, _buffer, _bufferSize);
}

void TCPNetwork::handleErrors(QAbstractSocket::SocketError socketError)
{
    emit disconnected();
}

void TCPNetwork::sendPacket(IPacket &packet)
{
    packet.write();
    _socket->write((char *)&packet.getData(), packet.getDataSize());
    _socket->waitForBytesWritten(5000);
}

#include "moc_TCPNetwork.cpp"