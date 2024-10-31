/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Incoming
*/

#ifndef INCOMING_HPP_
#define INCOMING_HPP_

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <iostream>
#include <memory>

namespace gui 
{
    class Incoming : public QWidget
    {
        public:
            explicit Incoming(QWidget *parent);
            ~Incoming() = default;
            QPushButton *getAcceptButton();
            QPushButton *getRefuseButton();
            
        private:
            std::unique_ptr<QGridLayout> _layout;
            std::unique_ptr<QPushButton> _acceptButton;
            std::unique_ptr<QPushButton> _refuseButton;
            std::unique_ptr<QLabel> _title;
    };
}
#endif /* !INCOMING_HPP_ */
