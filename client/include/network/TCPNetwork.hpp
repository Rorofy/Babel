/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** TCPNetwork
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <QTcpSocket>
#include <QThread>
#include <QtNetwork>
#include "network/INetwork.hpp"
#include "network/packets/PacketManager.hpp"

class TCPNetwork : public QObject, public INetwork {
    Q_OBJECT

    public:
        TCPNetwork();
        virtual ~TCPNetwork() {};

        void connectTo(const std::string &host, int port);
        void sendPacket(IPacket &packet) override;

    signals:
        void friendRequest(const std::string &username);
        void newFriend(const std::string &username);
        void friendUpdate(const std::vector<std::string> &friends);
        void loginAccepted(void);
        void registerAccepted(void);
        void receiveCall(const std::vector<std::string> &ips);
        void disconnected(void);

    public slots:
        void addFriend(const std::string &username);
        void answerRequest(const std::string &username, bool asnwer);
        void registerStart(const std::string &username, const std::string &password);
        void login(const std::string &username, const std::string &password);
        void startCall(const std::vector<std::string> &peers);

    private slots:
        void readData();
        void handleErrors(QAbstractSocket::SocketError socketError);
        void connectHandler();
        void disconnect();

    private:
        void initCallbacks(void);

    private:
        std::array<char, 4096> _buffer;
        std::size_t _bufferSize;
        QTcpSocket *_socket;
        std::string _token;
        PacketManager _packetManager;

};

#endif /* !NETWORK_HPP_ */
