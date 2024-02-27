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
    for (int i = 0; i < 4; i++)
    {
        if (obj[i][0] == '#' || obj[i][0] == '&' || obj[i][0] == '+' || obj[i][0] == '-' || obj[i][0] == '!')
        {
            user->ReplyMsg(ERR_ERRONEUSNICKNAME(user->getNickname(), obj[i]));
            return ;
        }
    }
    user->setUserName(obj[0]);
    user->setHostName(obj[1]);
    user->setNickname(obj[2]);
    user->setName(obj[3]);
    // if (user->getNickname() != "")
    //     user->setRegistration(true);
    _Server->setUser(user, user->getNickname(), user->getFd());
}