/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Register
*/

#ifndef REGISTER_HPP_
#define REGISTER_HPP_

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
    class Register : public QWidget
    {
        public:
            explicit Register(QWidget *parent);
            ~Register() = default;
            QPushButton *getRegisterButton();
            QPushButton *getReturnButton();
            QLineEdit *getRegisterText();
            QLineEdit *getPasswordText();

        private:
            std::unique_ptr<QGridLayout> _layout;
            std::unique_ptr<QLabel> _title;
            std::unique_ptr<QLineEdit> _registerText;
            std::unique_ptr<QLineEdit> _passwordText;
            std::unique_ptr<QPushButton> _registerButton;
            std::unique_ptr<QPushButton> _returnButton;
    };
}
#endif /* !REGISTER_HPP_ */
