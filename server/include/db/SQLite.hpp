/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** SQLite
*/

#ifndef SQLITE_HPP_
#define SQLITE_HPP_

#include <sqlite3.h>
#include <vector>
#include "IDataBase.hpp"

class SQLite : public IDataBase {
    public:
        SQLite();
        ~SQLite();

        void userAdd(const std::string &username, const std::string &password) override;
        void userAddFriend(const std::string &username, const std::string &frie) override;
        void userAddFriendRequest(const std::string &username, const std::string &frie) override;
        void userRemoveFriendRequest(const std::string &username, const std::string &frie) override;
        bool userHaveFriend(const std::string &username, const std::string &frie, int pending) override;
        [[nodiscard]] bool userExist(const std::string &username) override;
        [[nodiscard]] bool userPassword(const std::string &username, const std::string &password) override;
        [[nodiscard]] std::vector<std::string> getUserFriends(const std::string &username) override;

        std::vector<std::string> query(const std::string &query);

    private:
        static int callback(void *data, int argc, char **argv, char **e);

    private:
        sqlite3 *_db;
};

#endif /* !SQLITE_HPP_ */
