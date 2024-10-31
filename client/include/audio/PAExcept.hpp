/*
** EPITECH PROJECT, 2021
** B-CPP-500-PAR-5-1-babel-guerlain.blanchard
** File description:
** PAExcept
*/

#ifndef PAEXCEPT_HPP_
#define PAEXCEPT_HPP_

#include <exception>
#include <string>

class PAExcept : public std::exception {
    public:
        PAExcept(std::string const &message, int const value) throw();
        ~PAExcept() = default;

        [[ nodiscard ]]std::string getPAException();
        [[ nodiscard ]]int getExitValue();
    private:
        std::string _errorMessage;
        int _exitValue;
};

#endif /* !PAEXCEPT_HPP_ */
