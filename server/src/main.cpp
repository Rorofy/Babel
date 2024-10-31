/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** main
*/

#include "Server.hpp"

int main()
{
    auto &server = Server::provide();

    server.start();
}