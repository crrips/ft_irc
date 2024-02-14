#include "Channel.hpp"

// Channel::Channel()
// {
// }

// Channel::~Channel()
// {
    
// }

// Channel::Channel(Channel const &obj)
// {
//     *this = obj;
// }

Channel::Channel(std::string const &name, std::string const &pass, User *admin) : _name(name), _pass(pass), _admin(admin)
{

}

std::string Channel::getName()
{
    return (_name);
}

std::string Channel::getPass()
{
    return (_pass);
}

std::string Channel::getTopic()
{
    return (_topic);
}

std::vector<User *> Channel::getUsers()
{
    return (_users);
}

User *Channel::getUser(std::string const &nickname)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if ((*it)->getNickname() == nickname)
            return (*it);
    }
    return (NULL);
}

void Channel::setName(std::string const &name)
{
    _name = name;
}

void Channel::setPass(std::string const &pass)
{
    _pass = pass;
}

void Channel::setTopic(std::string const &topic)
{
    _topic = topic;
}

bool Channel::isAdmin(User *user)
{
    if (user == _admin)
        return (true);
    return (false);
}

bool Channel::isExist(User *user)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if (*it == user)
            return (true);
    }
    return (false);
}

void Channel::join(User *user)
{
    _users.push_back(user);
}

void Channel::part(User *user)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if (*it == user)
        {
            _users.erase(it);
            break;
        }
    }
}

void Channel::kick(User *user, std::string const &msg)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if (*it == user)
        {
            _users.erase(it);
            break;
        }
    }
    user->SendMsg(msg);
}

void Channel::sendMsg(User *user, std::string const &msg)
{
    for (std::vector<User *>::iterator it = _users.begin(); it != _users.end(); ++it)
    {
        if (*it != user)
            (*it)->SendMsg(msg);
    }
}
