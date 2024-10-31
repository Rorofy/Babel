/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** SQLite
*/

#include <iostream>
#include "db/SQLite.hpp"

SQLite::SQLite()
{
    int error = sqlite3_open("test.db", &_db);

    if (+error || sqlite3_exec(_db,  "CREATE TABLE IF NOT EXISTS users(username TEXT NOT NULL, password TEXT NOT NULL); CREATE TABLE IF NOT EXISTS friends(username TEXT NOT NULL, friend_username TEXT NOT NULL, pending INT NOT NULL, FOREIGN KEY(username) REFERENCES users(username), FOREIGN KEY(friend_username) REFERENCES users(username));",
                                nullptr, nullptr, nullptr) != SQLITE_OK)
    {
        std::cerr << "Babel Server SQLite DB Error: " << std::endl <<  sqlite3_errmsg(_db) << std::endl;
        exit(84);
    }
}

SQLite::~SQLite()
{
    sqlite3_close(_db);
}

std::vector<std::string> SQLite::query(const std::string &query)
{
    int error = 0;
    char *errorMessage = nullptr;
    std::vector<std::string> data;

    error = sqlite3_exec(_db, query.c_str(), &callback, &data, &errorMessage);
    if (error != SQLITE_OK)
        std::cerr << "Babel Server SQLite DB Error: " << std::endl << errorMessage << std::endl;
    return data;
}

void SQLite::userAdd(const std::string &username, const std::string &password)
{
    query("INSERT INTO users VALUES (\"" + username + "\", \"" + password + "\");");
}

void SQLite::userAddFriend(const std::string &username, const std::string &fri)
{
    query("UPDATE friends SET pending = 0 WHERE username = \"" + username + "\" AND friend_username = \"" + fri + "\";");
    query("INSERT INTO friends VALUES (\"" + fri + "\", \"" + username + "\", 0);");
}

bool SQLite::userExist(const std::string &username)
{
    return !query("SELECT username FROM users WHERE username=\"" + username + "\";").empty();
}

std::vector<std::string> SQLite::getUserFriends(const std::string &username)
{
    return query("SELECT friend_username, pending FROM friends WHERE username = \"" + username + "\" AND pending = 0 UNION SELECT username, pending FROM friends WHERE friend_username = \"" + username + "\" AND pending = 1;");
}

int SQLite::callback(void *data, int argc, char **argv, char **e)
{
    auto *queryResults = reinterpret_cast<std::vector<std::string> *>(data);

    for (int i = 0; i < argc; i++)
        queryResults->push_back(argv[i]);
    return 0;
}

bool SQLite::userPassword(const std::string &username, const std::string &password)
{
    return !query("SELECT * FROM users WHERE username=\"" + username + "\" AND password = \"" + password + "\"").empty();
}

void SQLite::userAddFriendRequest(const std::string &username, const std::string &frie)
{
    query("INSERT INTO friends VALUES (\"" + username + "\", \"" + frie + "\", 1);");
}

void SQLite::userRemoveFriendRequest(const std::string &username, const std::string &frie)
{
    query("DELETE friends SET pending = 1 WHERE username = \"" + username + "\" AND friend_username = \"" + frie + "\";");
}

bool SQLite::userHaveFriend(const std::string &username, const std::string &frie, int pending)
{
    return !query("SELECT * FROM friends WHERE username = \"" + username + "\" AND friend_username = \"" + frie + "\" AND pending = " + std::to_string(pending)).empty();
}