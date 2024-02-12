#include "Commands.hpp"

void Commands::Topic(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 1)
    {
        user->SendMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "TOPIC"));
        return ;
    }
    Channel *channel = _Server->getChannel(obj[0]);
    if (channel == NULL)
    {
        user->SendMsg(ERR_NOSUCHCHANNEL(user->getNickname(), obj[0]));
        return ;
    }
    if (channel->getUser(user->getNickname()) == NULL)
    {
        user->SendMsg(ERR_NOTONCHANNEL(user->getNickname(), obj[0]));
        return ;
    }
    if (channel->getTopic().empty())
    {
        user->SendMsg(RPL_NOTOPIC(user->getNickname(), channel->getName()));
        return ;
    }
    if (!channel->isAdmin(user))
    {
        user->SendMsg(ERR_CHANOPRIVSNEEDED(user->getNickname(), channel->getName()));
        return ;
    }
    if (obj.size() == 2)
        channel->setTopic(obj[1]);
    user->SendMsg(RPL_TOPIC(user->getNickname(), channel->getName(), channel->getTopic()));
}
