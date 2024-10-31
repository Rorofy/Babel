/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** main
*/

#include <QApplication>
#include <QWidget>
#include <iostream>
#include "Client.hpp"

Q_DECLARE_METATYPE(std::string);

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Client client;

    qRegisterMetaType<std::string>();
    client.start(argv[1], std::stoi(argv[2]));
    return app.exec();
}