/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <QObject>
#include "audio/Audio.hpp"
#include "gui/MainWindow.hpp"
#include "network/TCPNetwork.hpp"
#include "network/UDPNetwork.hpp"

class Client : public QObject {
    Q_OBJECT

    public:
        Client() = default;
        ~Client() = default;

        void start(const std::string &host, int port);

    public:
        [[nodiscard]] gui::MainWindow &getGui();
        [[nodiscard]] TCPNetwork &getNetwork();
        [[nodiscard]] std::vector<std::string> &getFriends();
        [[nodiscard]] std::vector<std::string> &getFriendRequests();

    public slots:
        void receiveCall(const std::vector<std::string> &ips);

    private:
        Audio _audio;
        gui::MainWindow _gui;
        TCPNetwork _network;
        std::unique_ptr<UDPNetwork> _udpNetwork;
        std::vector<std::string> _friends;
        std::vector<std::string> _friendRequest;
};

#endif /* !CLIENT_HPP_ */
