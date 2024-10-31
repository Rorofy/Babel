/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Client
*/

#include "Client.hpp"

void Client::start(const std::string &host, int port)
{
    connect(&_network, &TCPNetwork::receiveCall, this, &Client::receiveCall);
    _network.connectTo(host, port);
    _gui.initCallbacks(_network);
    _gui.show();
}

void Client::receiveCall(const std::vector<std::string> &ips)
{
    _udpNetwork = std::make_unique<UDPNetwork>(ips);
    _audio.connect(&_audio, &Audio::recordReady, _udpNetwork.get(), &UDPNetwork::sendVoice);
    _audio.connect(_udpNetwork.get(), &UDPNetwork::recordReceive, &_audio, &Audio::playSound);
    _audio.startRecord();
}

gui::MainWindow &Client::getGui()
{
    return _gui;
}

TCPNetwork &Client::getNetwork()
{
    return _network;
}

std::vector<std::string> &Client::getFriends()
{
    return _friends;
}

std::vector<std::string> &Client::getFriendRequests()
{
    return _friendRequest;
}

#include "moc_Client.cpp"