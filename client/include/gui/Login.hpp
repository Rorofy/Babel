/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Login
*/

#ifndef LOGIN_HPP_
#define LOGIN_HPP_

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
    class Login : public QWidget
    {
        public:
            explicit Login(QWidget *parent);
            ~Login() = default;
            QPushButton *getLoginButton();
            QLineEdit *getLoginText();
            QLineEdit *getPasswordText();
            QPushButton *getRegisterButton();
            std::string getUsername();
            void setUsername(const std::string);

        private:
            std::unique_ptr<QGridLayout> _layout;
            std::unique_ptr<QLabel> _title;
            std::unique_ptr<QLineEdit> _loginText;
            std::unique_ptr<QLineEdit> _passwordText;
            std::unique_ptr<QPushButton> _loginButton;
            std::unique_ptr<QPushButton> _registerButton;
            std::string _username;
    };
}
#endif /* !LOGIN_HPP_ */
