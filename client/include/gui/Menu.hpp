/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include "network/TCPNetwork.hpp"
#include "gui/Add.hpp"

namespace gui
{
    class Menu : public QWidget
    {
        Q_OBJECT

        public:
            explicit Menu(QWidget *parent);
            ~Menu() = default;

            QPushButton *getCallButton();
            void initCallbacks(TCPNetwork &network);
            void updateFriends(const std::vector<std::string> &friends);

        private:
            std::unique_ptr<QGridLayout> _layout;
            std::unique_ptr<QLabel> _title;
            std::unique_ptr<QPushButton> _callButton;
            gui::Add _add;
            
    };
};

#endif /* !MENU_HPP_ */
