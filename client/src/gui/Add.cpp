/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Add
*/

#include "gui/Add.hpp"

gui::Add::Add() :
QWidget(),
_layout(std::make_unique<QGridLayout>()),
_contactSearch(std::make_unique<QLineEdit>()),
_addButton(std::make_unique<QPushButton>()),
_contactList(std::make_unique<QListWidget>())
{
    _contactSearch->setPlaceholderText("username");
    _contactSearch->setAutoFillBackground(true);
    _contactSearch->setTextMargins(5, 0, 0, 0);

    _addButton->setText("Add");
    _layout->addWidget(_contactList.get(), 0, 0);
    _layout->addWidget(_contactSearch.get(), 1, 0);
    _layout->addWidget(_addButton.get(), 2, 0);

    setLayout(_layout.get());

    connect(_addButton.get(), &QPushButton::clicked, this, &gui::Add::onAddButtonClicked);
    connect(_contactSearch.get(), &QLineEdit::returnPressed, this, &gui::Add::onAddButtonClicked);
}

void gui::Add::onAddButtonClicked()
{
    QString contact = _contactSearch->text();

    if (contact.isEmpty())
        return;
    _contactSearch->clear();
    emit addFriend(contact.toStdString());
}

void gui::Add::newFriend(const std::string &username)
{
    QListWidgetItem *newItem = new QListWidgetItem();

    newItem->setText(QString::fromStdString(username));
    _contactList->insertItem(0, newItem);
}

void gui::Add::clearFriends(void)
{
    _contactList->clear();
}

std::string gui::Add::getSelectedContact()
{
    return _contactList->currentItem()->text().toStdString();
}

#include "gui/moc_Add.cpp"