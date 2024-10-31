/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Request
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

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
    class Request : public QWidget
    {
        Q_OBJECT

        public:
            explicit Request(QWidget *parent);
            ~Request() = default;

            void clearFriends(void);

            QPushButton *getAcceptButton();
            QPushButton *getRefuseButton();
            std::string getSelectedRequest();

        public slots:
            void addFriendRequest(const std::string &username);
            void removeFriendRequest(const std::string &username);

        private:
            std::unique_ptr<QGridLayout> _layout;
            std::unique_ptr<QPushButton> _acceptButton;
            std::unique_ptr<QPushButton> _refuseButton;
            std::unique_ptr<QListWidget> _requestList;
            std::unique_ptr<QLabel> _title;
    };
}
#endif /* !REQUEST_HPP_ */
