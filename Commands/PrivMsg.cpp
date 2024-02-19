#include "Commands.hpp"

void Commands::PrivMsg(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 2)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "PRIVMSG"));
        return ;
    }

    std::string targetUser = obj[0];
    std::string message = obj[1];

    if (message[0] == ':')
        message.erase(0, 1);

    for (size_t i = 2; i < obj.size(); i++)
        message += " " + obj[i];

    if (targetUser[0] != '#' && targetUser[0] != '&')
    {
        User *target = _Server->getUser(targetUser);
        if (!target)
        {
            user->ReplyMsg(ERR_NOSUCHNICK(user->getNickname(), targetUser));
            return ;
        }
        target->ReplyMsg(RPL_MSG(user->getNickname(), "PRIVMSG", targetUser, message));
    }
    else
    {
        Channel *channel = _Server->getChannel(targetUser);
        if (!channel)
        {
            user->ReplyMsg(ERR_NOSUCHCHANNEL(user->getNickname(), targetUser));
            return ;
        }
        if (!channel->isExist(user))
        {
            user->ReplyMsg(ERR_NOTONCHANNEL(user->getNickname(), targetUser));
            return ;
        }
        channel->sendMsg(user, RPL_MSG(user->getNickname(), "PRIVMSG", targetUser, message));
    }
}