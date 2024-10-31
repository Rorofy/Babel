/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Register
*/

#include "gui/Register.hpp"

gui::Register::Register(QWidget *parent) :
_title(std::make_unique<QLabel>()),
_layout(std::make_unique<QGridLayout>()),
_registerButton(std::make_unique<QPushButton>()),
_registerText(std::make_unique<QLineEdit>()),
_returnButton(std::make_unique<QPushButton>()),
_passwordText(std::make_unique<QLineEdit>())
{
    _layout->addWidget(_title.get(), 0, 0, Qt::AlignCenter);
    _layout->addWidget(_registerText.get(), 1, 0, Qt::AlignCenter);
    _layout->addWidget(_passwordText.get(), 2, 0, Qt::AlignCenter);
    _layout->addWidget(_registerButton.get(), 3, 0, Qt::AlignCenter);
    _layout->addWidget(_returnButton.get(), 4, 0, Qt::AlignCenter);

    _title->setText("Register");
    _registerButton->setText("Register");
    _registerText->setPlaceholderText("username");
    _registerText->setAutoFillBackground(true);
    _registerText->setTextMargins(5, 0, 0, 0);
    _passwordText->setPlaceholderText("password");
    _passwordText->setAutoFillBackground(true);
    _passwordText->setTextMargins(5, 0, 0, 0);
    _returnButton->setText("Return");

    _title->setStyleSheet("color: white;");

    setLayout(_layout.get());
}

QPushButton *gui::Register::getRegisterButton()
{
    return _registerButton.get();
}

QPushButton *gui::Register::getReturnButton()
{
    return _returnButton.get();
}

QLineEdit *gui::Register::getRegisterText()
{
    return _registerText.get();
}

QLineEdit *gui::Register::getPasswordText()
{
    return _passwordText.get();
}