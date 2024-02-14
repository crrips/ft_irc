#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include <sys/socket.h> //works only with linux
#include "Channel.hpp"
#include <vector>
#include "Parsing.hpp"

class Channel;

class User
{
private:
    std::vector<Channel *> _Channel;
    std::string _Nickname;
    std::string _UserName;
    std::string _HostName;
    std::string _Name;
    bool _Registration;
    bool _Pass;
    int _FileDescriptor;

public:
    User();
    ~User();
    User(int fd, std::string const &hostname);

    bool _Quit;
    std::string _Buffer;

    bool getPass();
    void setPass();
    std::string getHostName() const;
    std::string getNickname() const;
    std::string getUserName() const;
    std::string getName() const;
    std::string getMessage() const;
    bool isQuit() const;

    void setHostName(const std::string hostname);
    void setNickname(const std::string nickname);
    void setUserName(const std::string username);
    void setName(const std::string name);
    void setRegistration(bool reg);
    void setQuit(bool status);

    bool IsRegistered();                    
    void Registration();                    
    void ReplyMsg(const std::string &msg);  
    void SendMsg(const std::string &msg);   
    void JoinTheChannel(Channel *channel);  
    void LeaveTheChannel(Channel *channel); 
    void DeleteUser(int del);
};

#endif