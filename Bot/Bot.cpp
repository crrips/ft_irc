#include "Bot.hpp"

Bot::Bot(std::string host, int port, std::string psw, std::string nick) : _Host(host), _Port(port), _Psw(psw), _Nick(nick)
{
    if (InitTheBot() == -1) 
        return ; 
    RunTheBot();
}

Bot::~Bot()
{

}

int Bot::ConnectTheBot()
{
    if (connect(_Socket, (struct sockaddr *)&_Address, sizeof(_Address)) < 0)
    {
        std::cout << "Error: Connection failed!" << std::endl;
        return -1;
    }
    std::cout<<"Connected successfully!\n";
    return 0;
}

int Bot::InitTheBot()
{
    _BytesRead = 0;
    _BytesWritten = 0;
    if ((_Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout<<"Error: Socket failed!"<<std::endl;
        return -1;
    }
    _Address.sin_family = AF_INET;
    _Address.sin_port = htons(_Port);
    std::cout<<"Host: "<< _Host <<std::endl;

    if(inet_pton(AF_INET, _Host.c_str(), &_Address.sin_addr) <= 0) 
    { 
        std::cout<<"Error: Invalid address!\n";
        return -1;
    }
    return 0;
}

void Bot::SendMsg(std::string const &msg)
{
    std::string buffer = msg + "\r\n";
    _BytesWritten += send(_Socket, buffer.c_str(), strlen(buffer.c_str()), 0);
}

void Bot::RunTheBot()
{

    char buffer[5000];
    std::string data;
    
    while (1)
    {
        if (connect(_Socket, (struct sockaddr *)&_Address, sizeof(_Address)) != -1)
        {
            fcntl(_Socket, F_SETFL, O_NONBLOCK);
            SendMsg("PASS " + _Psw);
            SendMsg("USER " + _Nick + " " + ToString(_Port) + " " + _Host + " :Noname");
            SendMsg("NICK " + _Nick);
            
            while (1)
            {
                memset(&buffer, 0, sizeof(buffer));
                int value = recv(_Socket, (char*)&buffer, sizeof(buffer), 0);
                if (value == 0)
                    break; 
                _BytesRead += value;
                data = "";
                data.append(buffer);
                if (!data.empty())
                {
                    if (Handle(buffer))
                        break;
                }
            }
            break;
        }
    }
    close(_Socket);
    std::cout<<"The session was done :("<<std::endl;
}

std::string Bot::Parsing(std::string &data, std::string *msg)
{
    _BUser = "";
    if (data.find("PRIVMSG") > data.size())
        return "";
    _BUser = data.substr(1, data.find("!") - 1);
    std::string tmp = data.substr(data.find(":", 1) + 1, data.size());
    std::string command = tmp;
    tmp = tmp.substr(tmp.find(":", 0) + 1, tmp.size());
    
    if (tmp.size() < command.size())
        command = command.substr(0, command.size() - tmp.size());
    else
        tmp = "";
    tmp = trim(tmp, " :\r\n\t");
    command = trim(command," :\r\n");
    *msg = tmp;
    return command;
}

std::string Bot::Hello()
{
    return "Hello, my name is " + _Nick + "\r\n";
}

int Bot::Handle(std::string msg)
{
    std::string text;
    std::string command = Parsing(msg, &text);

    std::cout << "Command: " << command << std::endl;

    if (_BUser.empty() || command.empty())
        return 0;
    else if (command == "SAYHELLO")
        text = Hello();
    else if (command == "EXIT")
        return 1;
    else
        text = "Wrong input\r\n";
    if (!text.empty())
        SendMsg("PRIVMSG " + _BUser + " " + text);
    return 0;
}
