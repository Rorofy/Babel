/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** PacketLogin
*/

#ifndef PACKETFRIEND_HPP_
#define PACKETFRIEND_HPP_

#include "APacket.hpp"
#include "network/Protocol.hpp"

class PacketFriendAdd : public APacket {
    public:
        PacketFriendAdd(const std::string &token = "", const std::string &friendName = "") :
            APacket(PACKET_FRIEND_ADD), _token(token), _friend(friendName) {}
        ~PacketFriendAdd() {};

        void write(void) override {
            writeString(_token);
            writeString(_friend);
        }

        void read(void) override {
            _token = readString();
            _friend = readString();
        }

        [[nodiscard]] const std::string &getToken() {return _token;};
        [[nodiscard]] const std::string &getFriend() {return _friend;};

    private:
        std::string _token;
        std::string _friend;
};

class PacketFriendAddAnswer : public APacket {
    public:
        PacketFriendAddAnswer(const std::string &user = "", bool answer = false) :
            APacket(PACKET_FRIEND_ADD_ANSWER), _user(user), _answer(answer) {}
        ~PacketFriendAddAnswer() {};

        void write(void) override {
            writeString(_user);
            writeBool(_answer);
        }

        void read(void) override {
            _user = readString();
            _answer = readBool();
        }

        [[nodiscard]] bool getAnswer() {return _answer;};
        [[nodiscard]] const std::string &getUser() {return _user;};

    private:
        std::string _user;
        bool _answer;
};

class PacketFriendRequest : public APacket {
    public:
        PacketFriendRequest(const std::string &user = "") :
            APacket(PACKET_FRIEND_REQUEST), _user(user) {}
        ~PacketFriendRequest() {};

        void write(void) override {
            writeString(_user);
        }

        void read(void) override {
            _user = readString();
        }

        [[nodiscard]] const std::string &getUser() {return _user;};

    private:
        std::string _user;
};

class PacketFriendRequestAnswer : public APacket {
    public:
        PacketFriendRequestAnswer(const std::string &token = "", const std::string &user = "", bool answer = false) :
            APacket(PACKET_FRIEND_REQUEST_ANSWER), _token(token), _user(user), _answer(answer) {}
        ~PacketFriendRequestAnswer() {};

        void write(void) override {
            writeString(_token);
            writeString(_user);
            writeBool(_answer);
        }

        void read(void) override {
            _token = readString();
            _user = readString();
            _answer = readBool();
        }

        [[nodiscard]] const std::string &getToken() {return _token;};
        [[nodiscard]] const std::string &getUser() {return _user;};
        [[nodiscard]] bool getAnswer() {return _answer;};

    private:
        std::string _token;
        std::string _user;
        bool _answer;
};
class PacketFriendsGet : public APacket {
    public:
        PacketFriendsGet(const std::string &token = "") :
            APacket(PACKET_FRIENDS_GET), _token(token) {}
        ~PacketFriendsGet() {};

        void write(void) override {
            writeString(_token);
        }

        void read(void) override {
            _token = readString();
        }

        [[nodiscard]] const std::string &getToken() {return _token;};

    private:
        std::string _token;
};


class PacketFriendsGetAnswer : public APacket {
    public:
        PacketFriendsGetAnswer(const std::vector<std::string> &friends = {}) :
            APacket(PACKET_FRIENDS_GET_ANSWER), _friends(friends) {};
        ~PacketFriendsGetAnswer() {};

        void write(void) override {
            writeInt(_friends.size());
            for (auto &x : _friends)
                writeString(x);
        }

        void read(void) override {
            int count = readInt();

            for (int i = 0; i < count; i++)
                _friends.push_back(readString());
        }

        [[nodiscard]] std::vector<std::string> getFriends() {return _friends;};

    private:
        std::vector<std::string> _friends;
};

#endif /* !PACKETFRIEND_HPP_ */