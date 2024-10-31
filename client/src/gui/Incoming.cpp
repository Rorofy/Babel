/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Incoming
*/

#include "gui/Incoming.hpp"

gui::Incoming::Incoming(QWidget *parent) :
_layout(std::make_unique<QGridLayout>()),
_title(std::make_unique<QLabel>()),
_acceptButton(std::make_unique<QPushButton>()),
_refuseButton(std::make_unique<QPushButton>())
{
    _layout->addWidget(_title.get(), 0, 0, Qt::AlignCenter);
    _layout->addWidget(_acceptButton.get(), 1, 0, Qt::AlignCenter);
    _layout->addWidget(_refuseButton.get(), 2, 0, Qt::AlignCenter);
    _title->setText("INCOMING CALL...");
    _acceptButton->setText("Accept");
    _refuseButton->setText("Refuse");

    _title->setStyleSheet("color: white;");

    setLayout(_layout.get());
}

QPushButton *gui::Incoming::getAcceptButton()
{
    return _acceptButton.get();
}

QPushButton *gui::Incoming::getRefuseButton()
{
    return _refuseButton.get();
}
