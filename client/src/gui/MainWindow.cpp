/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** MainWindow
*/

#include "Client.hpp"
#include "network/packets/PacketAuth.hpp"
#include "network/packets/PacketCall.hpp"

gui::MainWindow::MainWindow(QWidget *parent) : 
QMainWindow(),
_parent(std::make_unique<QStackedWidget>()),
_pages(std::make_unique<QComboBox>()),
_tab(std::make_unique<QTabWidget>()),
_menu(_parent.get()),
_login(_parent.get()),
_calling(_parent.get()),
_connectionLost(_parent.get()),
_request(_parent.get()),
_register(_parent.get()),
_incoming(_parent.get())
{
    QPalette palette;

    setWindowTitle("Babel");
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    palette.setColor(QPalette::Window, QColor(70, 70, 70));
    _tab->setPalette(QColor(70, 70, 70));
    setAutoFillBackground(true);
    setPalette(palette);
    setupWidgets();
    setupConnects();
}

void gui::MainWindow::initCallbacks(TCPNetwork &network)
{
    connect(&network, &TCPNetwork::friendRequest, &_request, &Request::addFriendRequest);
    connect(&network, &TCPNetwork::friendUpdate, this, &MainWindow::updateFriends);
    connect(&network, &TCPNetwork::loginAccepted, this, &MainWindow::swapToTab);
    connect(&network, &TCPNetwork::registerAccepted, this, &MainWindow::swapToLogin);
    connect(&network, &TCPNetwork::receiveCall, this, &MainWindow::swapToCall);
    connect(&network, &TCPNetwork::disconnected, this, &MainWindow::swapToLost);
    connect(this, &MainWindow::loginStart, &network, &TCPNetwork::login);
    connect(this, &MainWindow::registerStart, &network, &TCPNetwork::registerStart);
    connect(this, &MainWindow::answerRequest, &network, &TCPNetwork::answerRequest);
    connect(this, &MainWindow::startCall, &network, &TCPNetwork::startCall);
    _menu.initCallbacks(network);
}

void gui::MainWindow::setupWidgets()
{
    _tab->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    _pages->addItem(tr("Login Page"));
    _pages->addItem(tr("Tab Page"));
    _pages->addItem(tr("Calling Page"));
    _pages->addItem(tr("Connection Lost Page"));
    _pages->addItem(tr("Register Page"));
    _pages->addItem(tr("Incoming Page"));
    _tab->addTab(&_menu, "Menu");
    _tab->addTab(&_request, "Friend Requests");
    _parent->addWidget(&_login);
    _parent->addWidget(&_calling);
    _parent->addWidget(&_connectionLost);
    _parent->addWidget(&_register);
    _parent->addWidget(&_incoming);
    _parent->addWidget(_tab.get());
    setCentralWidget(_parent.get());
}

void gui::MainWindow::setupConnects()
{
    connect(_pages.get(), QOverload<int>::of(&QComboBox::activated), _parent.get(), &QStackedWidget::setCurrentIndex);
    connect(_login.getLoginButton(), &QPushButton::clicked, this, &gui::MainWindow::onLoginButtonClickedFromLogin);
    connect(_menu.getCallButton(), &QPushButton::clicked, this, &gui::MainWindow::onCallButtonClickedFromMenu);
    connect(_calling.getHangUpButton(), &QPushButton::clicked, this, &gui::MainWindow::onHangUpButtonClickedFromCalling);
    connect(_request.getAcceptButton(), &QPushButton::clicked, this, &gui::MainWindow::onAcceptButtonClickedFromRequest);
    connect(_request.getRefuseButton(), &QPushButton::clicked, this, &gui::MainWindow::onRefuseButtonClickedFromRequest);
    connect(_register.getRegisterButton(), &QPushButton::clicked, this, &gui::MainWindow::onRegisterButtonClickedFromRegister);
    connect(_register.getReturnButton(), &QPushButton::clicked, this, &gui::MainWindow::onReturnButtonClickedFromRegister);
    connect(_login.getRegisterButton(), &QPushButton::clicked, this, &gui::MainWindow::onRegisterButtonClickedFromLogin);
    connect(_incoming.getAcceptButton(), &QPushButton::clicked, this, &gui::MainWindow::onAcceptButtonClickedFromIncoming);
    connect(_incoming.getRefuseButton(), &QPushButton::clicked, this, &gui::MainWindow:: onRefuseButtonClickedFromIncoming);
}

void gui::MainWindow::updateFriends(const std::vector<std::string> &friends)
{
    auto vec = friends;

    _request.clearFriends();
    for (int i = 0; i + 1 < vec.size(); i++) {
        if (vec[i+1] == "1") {
            _request.addFriendRequest(vec[i]);
            vec.erase(std::next(vec.begin(), i), std::next(vec.begin(), i+2));
            i --;
        } else
            vec.erase(std::next(vec.begin(), i+1));
    }
     _menu.updateFriends(vec);
}

void gui::MainWindow::onLoginButtonClickedFromLogin()
{
    QString loginText = _login.getLoginText()->text();
    QString passwordText = _login.getPasswordText()->text();

    if (loginText.isEmpty())
        return;
    emit loginStart(loginText.toStdString(), passwordText.toStdString());
}

void gui::MainWindow::onCallButtonClickedFromMenu()
{
    emit startCall(std::vector<std::string>({"t", "o"}));
}

void gui::MainWindow::onHangUpButtonClickedFromCalling()
{
    _parent->setCurrentWidget(_tab.get());
}

void gui::MainWindow::onRetryButtonClickedFromConnectionLost()
{
    _parent->setCurrentWidget(_tab.get());
}

void gui::MainWindow::onAcceptButtonClickedFromRequest()
{
    auto name = _request.getSelectedRequest();

    if (name.empty()) return;
    _request.removeFriendRequest(name);
    emit answerRequest(name, true);
}

void gui::MainWindow::onRefuseButtonClickedFromRequest()
{
    auto name = _request.getSelectedRequest();

    _request.removeFriendRequest(name);
    emit answerRequest(name, false);
}

void gui::MainWindow::onRegisterButtonClickedFromRegister()
{
    auto username = _register.getRegisterText()->text().toStdString();
    auto password = _register.getPasswordText()->text().toStdString();

    if (username.empty() || username.find_first_not_of(' ') == std::string::npos){
        std::cout << "Babel: Invalid auth credidentiel" << std::endl;
        return;
    }
    emit registerStart(username, password);
}

void gui::MainWindow::onReturnButtonClickedFromRegister()
{
    _parent->setCurrentWidget(&_login);
}

void gui::MainWindow::onRegisterButtonClickedFromLogin()
{
    _parent->setCurrentWidget(&_register);
}

void gui::MainWindow::onAcceptButtonClickedFromIncoming()
{
    _parent->setCurrentWidget(&_calling);
}

void gui::MainWindow::onRefuseButtonClickedFromIncoming()
{
    _parent->setCurrentWidget(_tab.get());
}

void gui::MainWindow::displayIncomingCallPage()
{
    _parent->setCurrentWidget(&_incoming);
}

void gui::MainWindow::swapToLogin()
{
    _parent->setCurrentWidget(&_login);
}

void gui::MainWindow::swapToTab()
{
    _parent->setCurrentWidget(_tab.get());
}

void gui::MainWindow::swapToCall()
{
    _parent->setCurrentWidget(&_calling);
}

void gui::MainWindow::swapToLost()
{
    _parent->setCurrentWidget(&_connectionLost);
}

#include "gui/moc_MainWindow.cpp"