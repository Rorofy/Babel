/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** MainWindow
*/

#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QFontDatabase>
#include <QComboBox>
#include <QPalette>
#include <QTabWidget>
#include <memory>
#include "gui/Menu.hpp"
#include "gui/Login.hpp"
#include "gui/Calling.hpp"
#include "gui/ConnectionLost.hpp"
#include "gui/Request.hpp"
#include "gui/Register.hpp"
#include "gui/Incoming.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600 

#include "network/TCPNetwork.hpp"

namespace gui 
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = 0);
            ~MainWindow() = default;

            void initCallbacks(TCPNetwork &network);
            void displayIncomingCallPage();

        signals:
            void loginStart(const std::string &name, const std::string &password);
            void registerStart(const std::string &name, const std::string &password);
            void answerRequest(const std::string &name, bool answer);
            void startCall(const std::vector<std::string> &peers);

        public slots:
            void updateFriends(const std::vector<std::string> &friends);
            void swapToLogin(void);
            void swapToTab(void);
            void swapToCall(void);
            void swapToLost(void);

        private:
            void onLoginButtonClickedFromLogin();
            void onCallButtonClickedFromMenu();
            void onHangUpButtonClickedFromCalling();
            void onRetryButtonClickedFromConnectionLost();
            void onAcceptButtonClickedFromRequest();
            void onRefuseButtonClickedFromRequest();
            void onRegisterButtonClickedFromRegister();
            void onReturnButtonClickedFromRegister();
            void onRegisterButtonClickedFromLogin();
            void onAcceptButtonClickedFromIncoming();
            void onRefuseButtonClickedFromIncoming();
            void setupConnects();
            void setupWidgets();

            std::unique_ptr<QStackedWidget> _parent;
            std::unique_ptr<QComboBox> _pages;
            std::unique_ptr<QTabWidget> _tab;
            gui::Menu _menu;
            gui::Login _login;
            gui::Calling _calling;
            gui::Request _request;
            gui::Register _register;
            gui::ConnectionLost _connectionLost;
            gui::Incoming _incoming;
    };
}
#endif /* !MAINWINDOW_HPP_ */
