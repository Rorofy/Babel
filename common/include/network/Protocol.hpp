/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

const int PACKET_TOKEN = 300;
const int PACKET_REGISTER = 200;
const int PACKET_REGISTER_ANSWER = 301;
const int PACKET_LOGIN = 201;
const int PACKET_LOGIN_ANSWER = 302;

const int PACKET_FRIEND_ADD = 202;
const int PACKET_FRIEND_ADD_ANSWER = 303;
const int PACKET_FRIEND_REQUEST = 202;
const int PACKET_FRIEND_REQUEST_ANSWER = 304;
const int PACKET_FRIENDS_GET = 203;
const int PACKET_FRIENDS_GET_ANSWER = 305;

const int PACKET_CALL = 310;
const int PACKET_CALL_REQUEST = 210;
const int PACKET_CALL_DATA = 100;

#endif /* !PROTOCOL_HPP_ */