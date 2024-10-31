/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** ConnectionLost
*/

#ifndef CONNECTIONLOST_HPP_
#define CONNECTIONLOST_HPP_

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <memory>
#include <iostream>

namespace gui
{
    class ConnectionLost : public QWidget
    {
        public:
            explicit ConnectionLost(QWidget *parent);
            ~ConnectionLost() = default;
            QPushButton *getRetryButton();

        private:
            std::unique_ptr<QGridLayout>_layout;
            std::unique_ptr<QPushButton> _retryButton;
            std::unique_ptr<QLabel> _text;
    };
}
#endif /* !CONNECTIONLOST_HPP_ */
