/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard [WSL: Ubuntu]
** File description:
** PacketAuth
*/

#ifndef PACKETAUTH_HPP_
#define PACKETAUTH_HPP_

#include "network/Protocol.hpp"
#include "network/packets/APacket.hpp"

class PacketToken : public APacket {
    public:
        PacketToken(const std::string &token = "") :
            APacket(PACKET_TOKEN), _token(token) {};
        ~PacketToken() {};

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

class PacketRegister : public APacket {
    public:
        PacketRegister(const std::string &username = "", const std::string &password = "") :
            APacket(PACKET_REGISTER), _username(username), _password(password) {};
        ~PacketRegister() {};

        void write(void) override {
            writeString(_username);
            writeString(_password);
        }

        void read(void) override {
            _username = readString();
            _password = readString();
        }

        [[nodiscard]] const std::string &getUsername() {return _username;};
        [[nodiscard]] const std::string &getPassword() {return _password;};

    private:
        std::string _username;
        std::string _password;
};

class PacketRegisterAnswer : public APacket {
    public:
        PacketRegisterAnswer(const bool ok = false) :
            APacket(PACKET_REGISTER_ANSWER), _ok(ok) {};
        ~PacketRegisterAnswer() {};

        void write(void) override {
            writeBool(_ok);
        }

        void read(void) override {
            _ok = readBool();
        }

        [[nodiscard]] bool accepted() {return _ok;};

    private:
        bool _ok;
};

class PacketLogin : public APacket {
    public:
        PacketLogin(const std::string &token = "", const std::string &username = "", const std::string &password = "") :
            APacket(PACKET_LOGIN),
            _token(token),
            _username(username),
            _password(password) {};
        ~PacketLogin() {};

        void write(void) override {
            writeString(_token);
            writeString(_username);
            writeString(_password);
        }

        void read(void) override {
            _token = readString();
            _username = readString();
            _password = readString();
        }

        [[nodiscard]] const std::string &getToken() {return _token;};
        [[nodiscard]] const std::string &getUsername() {return _username;};
        [[nodiscard]] const std::string &getPassword() {return _password;};

    private:
        std::string _token;
        std::string _username;
        std::string _password;
};

class PacketLoginAnswer : public APacket {
    public:
        PacketLoginAnswer(const bool ok = false) :
            APacket(PACKET_LOGIN_ANSWER), _ok(ok) {};
        ~PacketLoginAnswer() {};

        void write(void) override {
            writeBool(_ok);
        }

        void read(void) override {
            _ok = readBool();
        }

        [[nodiscard]] bool accepted() {return _ok;};

    private:
        bool _ok;
};

#endif /* !PACKETAUTH_HPP_ */