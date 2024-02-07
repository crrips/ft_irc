#ifndef SERVER_HPP  
# define SERVER_HPP

#include <iostream>
#include <string>
#include "Channel.hpp"

class Server
{
    private:
        int _Port;
        std::string &_Pass;
        Server();
        ~Server();
    public:
        int getPort();
        Channel *getName(std::string const &name);
        Channel *getChannel(std::string const &name);
};

#endif