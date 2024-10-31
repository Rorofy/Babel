/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Request
*/

#include "gui/Request.hpp"

gui::Request::Request(QWidget *parent) :
_layout(std::make_unique<QGridLayout>()),
_title(std::make_unique<QLabel>()),
_acceptButton(std::make_unique<QPushButton>()),
_refuseButton(std::make_unique<QPushButton>()),
_requestList(std::make_unique<QListWidget>())
{
    _layout->addWidget(_title.get(), 0, 0, Qt::AlignCenter);
    _layout->addWidget(_requestList.get(), 1, 0, Qt::AlignCenter);
    _layout->addWidget(_acceptButton.get(), 2, 0, Qt::AlignCenter);
    _layout->addWidget(_refuseButton.get(), 3, 0, Qt::AlignCenter);
    _title->setText("FRIEND REQUESTS");
    _acceptButton->setText("Accept");
    _refuseButton->setText("Refuse");

    _title->setStyleSheet("color: white;");

    setLayout(_layout.get());
}

QPushButton *gui::Request::getAcceptButton()
{
    return _acceptButton.get();
}

QPushButton *gui::Request::getRefuseButton()
{
    return _refuseButton.get();
}

std::string gui::Request::getSelectedRequest()
{
    auto text = _requestList->currentItem();

    return text != NULL ? text->text().toStdString() : "";
}

void gui::Request::addFriendRequest(const std::string &username)
{
    QString request = QString::fromStdString(username);
    QListWidgetItem *newItem = new QListWidgetItem();

    if (request.isEmpty())
        return;
    newItem->setText(request);
    _requestList->insertItem(0, newItem);
}

void gui::Request::removeFriendRequest(const std::string &username)
{
    auto list = _requestList->findItems(QString::fromStdString(username), Qt::MatchFixedString);

    for (auto &x : list) {
        _requestList->removeItemWidget(x);
        delete(x);
    }
}

void gui::Request::clearFriends(void)
{
    _requestList->clear();
}

#include "gui/moc_Request.cpp"