/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** UDPNetwork
*/

#ifndef UDPNETWORK_HPP_
#define UDPNETWORK_HPP_

#include <QTcpSocket>
#include "network/INetwork.hpp"
#include "network/packets/PacketManager.hpp"
#include <QMetaType>

class UDPNetwork : public QObject, public INetwork {
    Q_OBJECT

    public:
        UDPNetwork(const std::vector<std::string> &peers);
        virtual ~UDPNetwork() {};

        void connectTo(const std::string &port);
        void sendPacket(IPacket &packet) override;
        void sendPacketToAll(IPacket &packet);

        [[nodiscard]] std::string getIp(void) {return "";};

    signals:
        void recordReceive(const std::string &sound);

    public slots:
        void sendVoice(const std::string &sound);

    private:
        void initCallbacks(void);
    
    private slots:
        void readData();

    private:
        std::unique_ptr<QUdpSocket> _socket;
        PacketManager _packetManager;
        std::vector<std::string> _peers;
        std::array<char, 4096> _buffer;
};

#endif /* !UDPNETWORK_HPP_ */
