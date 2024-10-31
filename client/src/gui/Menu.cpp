/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Menu
*/

#include "gui/Menu.hpp"
#include "network/TCPNetwork.hpp"

gui::Menu::Menu(QWidget *parent) :
_title(std::make_unique<QLabel>()),
_layout(std::make_unique<QGridLayout>()),
_callButton(std::make_unique<QPushButton>())
{

    _layout->addWidget(_title.get(), 0, 0, Qt::AlignCenter);
    _layout->addWidget(&_add, 2, 0, Qt::AlignCenter);
    _layout->addWidget(_callButton.get(), 3, 0, Qt::AlignCenter);
    _title->setText("BABEL");
    _callButton->setText("Call");
    _title->setStyleSheet("color: white;");
    setLayout(_layout.get());

}

void gui::Menu::initCallbacks(TCPNetwork &network)
{
    connect(&_add, &Add::addFriend, &network, &TCPNetwork::addFriend);
    connect(&network, &TCPNetwork::newFriend, &_add, &Add::newFriend);
}

void gui::Menu::updateFriends(const std::vector<std::string> &friends)
{
    _add.clearFriends();
    for (auto &peer : friends)
        _add.newFriend(peer);
}

QPushButton *gui::Menu::getCallButton()
{
    return _callButton.get();
}

#include "gui/moc_Menu.cpp"
