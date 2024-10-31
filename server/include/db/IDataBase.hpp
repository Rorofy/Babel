/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** IDataBase
*/

#ifndef IDATABASE_HPP_
#define IDATABASE_HPP_

#include <string>

class IDataBase {
    public:
        IDataBase() {};
        virtual ~IDataBase() {};

        virtual void userAdd(const std::string &username, const std::string &password) = 0;
        virtual void userAddFriend(const std::string &username, const std::string &frie) = 0;
        virtual void userAddFriendRequest(const std::string &username, const std::string &frie) = 0;
        virtual void userRemoveFriendRequest(const std::string &username, const std::string &frie) = 0;
        virtual bool userHaveFriend(const std::string &username, const std::string &frie, int pending) = 0;
        [[nodiscard]] virtual bool userExist(const std::string &username) = 0;
        [[nodiscard]] virtual bool userPassword(const std::string &username, const std::string &password) = 0;
        [[nodiscard]] virtual std::vector<std::string> getUserFriends(const std::string &username) = 0;

};

#endif /* !IDATABASE_HPP_ */