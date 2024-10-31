/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Calling
*/

#include "gui/Calling.hpp"

gui::Calling::Calling(QWidget *parent) :
_layout(std::make_unique<QGridLayout>()),
_title(std::make_unique<QLabel>()),
_hangUpButton(std::make_unique<QPushButton>())
{
    _layout->addWidget(_title.get(), 0, 0, Qt::AlignCenter);
    _layout->addWidget(_hangUpButton.get(), 1, 0, Qt::AlignCenter);

    _title->setText("CALLING...");
    _hangUpButton->setText("Hang Up");

    _title->setStyleSheet("color: white;");

    setLayout(_layout.get());
}

QPushButton *gui::Calling::getHangUpButton()
{
    return _hangUpButton.get();
}