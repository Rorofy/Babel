/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** UDPNetwork
*/

#include "Client.hpp"
#include "network/UDPNetwork.hpp"
#include "network/packets/PacketCall.hpp"

UDPNetwork::UDPNetwork(const std::vector<std::string> &peers) :
    _peers(peers),
    _socket(std::make_unique<QUdpSocket>(this))
{
    _packetManager.registerPacket<PacketCallData>(PACKET_CALL_DATA, [this] (INetwork &sender, IPacket &packet) {
        emit recordReceive(((PacketCallData&)packet).getSound());
    });
    initCallbacks();
    connectTo("");
}

void UDPNetwork::initCallbacks()
{
    connect(_socket.get(), &QUdpSocket::readyRead, this, &UDPNetwork::readData);
}

void UDPNetwork::connectTo(const std::string &port)
{
    _socket->abort();
    if (!_socket->bind(QHostAddress::AnyIPv4, 6667))
        std::cout << "fail to bind udp network to the socket" << std::endl;
}

void UDPNetwork::sendPacket(IPacket &packet)
{
    packet.write();
}

void UDPNetwork::sendPacketToAll(IPacket &packet)
{
    packet.write();
    for (auto &i : _peers)
        _socket->writeDatagram((char *)&packet.getData(), packet.getDataSize(), QHostAddress(QString::fromStdString(i)), 6667);
}

void UDPNetwork::readData()
{
    while (_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = _socket->receiveDatagram();
        auto data = datagram.data();

        std::copy(data.begin(), data.end(), _buffer.begin());
        _packetManager.buildPacketFromData(*this, _buffer, _socket->pendingDatagramSize());
    }
}

void UDPNetwork::sendVoice(const std::string &voice)
{
    PacketCallData packet(voice);

    sendPacketToAll(packet);
}

#include "moc_UDPNetwork.cpp"