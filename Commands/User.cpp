#include "Commands.hpp"

void Commands::UserCmd(User *user, std::vector<std::string> obj)
{
    if (obj.empty() || obj.size() < 4)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "USER"));
        return ;
    }
    if (user->getUserName() != "")
    {
        user->ReplyMsg(ERR_ALREADYREGISTERED(user->getNickname()));
        return ;
    }
    user->setUserName(obj[0]);
    user->setHostName(obj[1]);
    user->setNickname(obj[2]);
    user->setName(obj[3]);
    if (user->getNickname() != "")
    {
        user->setRegistration(true);
        user->ReplyMsg(RPL_WELCOME(user->getNickname()));
    }
    // we don't saving user in server list bruuuuh
}
