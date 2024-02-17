#include "Commands.hpp"

void Commands::Notice(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 2)
    {
        user->SendMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "NOTICE"));
        return ;
    }

    std::string target = obj[0];
    std::string message = obj[1];

    if (target[0] == '#' || target[0] == '&')
    {
        Channel *channel = _Server->getChannel(target);
        if (channel == NULL)
        {
            user->SendMsg(ERR_NOSUCHCHANNEL(user->getNickname(), target));
            return ;
        }
        if (!channel->isExist(user))
        {
            user->SendMsg(ERR_NOTONCHANNEL(user->getNickname(), target));
            return ;
        }
        channel->sendMsg(user, RPL_NOTICE(user->getNickname(), target, message));
        return ;
    }
    else
    {
        User *targetUser = _Server->getUser(target);
        if (targetUser == NULL)
        {
            user->SendMsg(ERR_NOSUCHNICK(user->getNickname(), target));
            return ;
        }

        targetUser->SendMsg(RPL_NOTICE(user->getNickname(), target, message));
        user->SendMsg(RPL_NOTICE(user->getNickname(), target, message));
    }
}