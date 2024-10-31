/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** PAExcept
*/

#include "audio/PAExcept.hpp"

PAExcept::PAExcept(std::string const &message, int const value) throw() : _errorMessage(message), _exitValue(value)
{
}

std::string PAExcept::getPAException()
{
    return _errorMessage;
}

int PAExcept::getExitValue()
{
    return _exitValue;
}
