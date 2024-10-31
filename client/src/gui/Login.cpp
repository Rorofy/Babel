/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Login
*/

#include "gui/Login.hpp"

gui::Login::Login(QWidget *parent) :
_title(std::make_unique<QLabel>()),
_layout(std::make_unique<QGridLayout>()),
_loginButton(std::make_unique<QPushButton>()),
_loginText(std::make_unique<QLineEdit>()),
_passwordText(std::make_unique<QLineEdit>()),
_registerButton(std::make_unique<QPushButton>()),
_username("")
{
    _layout->addWidget(_title.get(), 0, 0, Qt::AlignCenter);
    _layout->addWidget(_loginText.get(), 1, 0, Qt::AlignCenter);
    _layout->addWidget(_passwordText.get(), 2, 0, Qt::AlignCenter);
    _layout->addWidget(_loginButton.get(), 3, 0, Qt::AlignCenter);
    _layout->addWidget(_registerButton.get(), 4, 0, Qt::AlignCenter);

    _title->setText("LOGIN");
    _loginButton->setText("Login");
    _registerButton->setText("Register");
    _loginText->setPlaceholderText("username");
    _loginText->setAutoFillBackground(true);
    _loginText->setTextMargins(5, 0, 0, 0);
    _passwordText->setPlaceholderText("password");
    _passwordText->setAutoFillBackground(true);
    _passwordText->setTextMargins(5, 0, 0, 0);
    
    _title->setStyleSheet("color: white;");

    setLayout(_layout.get());
}

QPushButton *gui::Login::getLoginButton()
{
    return _loginButton.get();
}

QLineEdit *gui::Login::getLoginText()
{
    return _loginText.get();
}

QLineEdit *gui::Login::getPasswordText()
{
    return _passwordText.get();
}

std::string gui::Login::getUsername()
{
    return _username;
}

void gui::Login::setUsername(std::string str)
{
    _username = str;
}

QPushButton *gui::Login::getRegisterButton()
{
    return _registerButton.get();
}

