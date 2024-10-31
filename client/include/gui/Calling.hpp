/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Calling
*/

#ifndef CALLING_HPP_
#define CALLING_HPP_

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
    class Calling : public QWidget
    {
        public:
            explicit Calling(QWidget *parent);
            ~Calling() = default;
            QPushButton *getHangUpButton();

        private:
            std::unique_ptr<QGridLayout> _layout;
            std::unique_ptr<QPushButton> _hangUpButton;
            std::unique_ptr<QLabel> _title;
    };
}
#endif /* !CALLING_HPP_ */
