/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Add
*/

#ifndef ADD_HPP_
#define ADD_HPP_

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <iostream>
#include <QListWidget>
#include <QString>
#include <QTextEdit>
#include <memory>

namespace gui
{
    class Add : public QWidget 
    {
        Q_OBJECT

        public:
            Add();
            ~Add() = default;
        
            void clearFriends(void);
            std::string getSelectedContact();

        signals:
            void addFriend(const std::string &name);

        public slots:
            void newFriend(const std::string &name);

        private slots:
            void onAddButtonClicked();

        private:
            std::unique_ptr<QGridLayout> _layout;
            std::unique_ptr<QLineEdit> _contactSearch;
            std::unique_ptr<QPushButton> _addButton;
            std::unique_ptr<QListWidget> _contactList;
    };
}

#endif /* !ADD_HPP_ */
