/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** ConnectionLost
*/

#include "gui/ConnectionLost.hpp"

gui::ConnectionLost::ConnectionLost(QWidget *parent) :
_layout(std::make_unique<QGridLayout>()),
_text(std::make_unique<QLabel>()),
_retryButton(std::make_unique<QPushButton>())
{
    _layout->addWidget(_text.get(), 0, 0, Qt::AlignCenter);
    _layout->addWidget(_retryButton.get(), 1, 0, Qt::AlignCenter);

    _text->setText("Connection Lost\nTry to reconnect");
    _retryButton->setText("Retry");
    _text->setStyleSheet("color: white;");

    setLayout(_layout.get());
}

QPushButton *gui::ConnectionLost::getRetryButton()
{
    return _retryButton.get();
}