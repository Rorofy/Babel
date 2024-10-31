/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include "network/packets/APacket.hpp"

class INetwork {
    public:
        INetwork() {};
        virtual ~INetwork() {};

        virtual void sendPacket(IPacket &data) = 0;
};

#endif /* !INETWORK_HPP_ */