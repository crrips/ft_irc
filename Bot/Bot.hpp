#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/uiocb.h>


class Bot
{
    private:
        int _Port;
        std::string _Psw;
        std::string _Nick;
        std::string _User;
        std::string _Host;
    public:
        Bot(int port, std::string const &psw);
        ~Bot();
};
        

#endif;