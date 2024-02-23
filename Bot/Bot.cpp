#include "Bot.hpp"

Bot::Bot(int port, std::string const &psw) : _Port(port), _Psw(psw)
{
    _Nick = "Bot";
    _User = "Bot"; 
    _Host = "localhost";
}

Bot::~Bot()
{
}

