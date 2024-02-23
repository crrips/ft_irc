#include "Commands.hpp"

void Commands::Nick(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "NICK"));
        return;
    }
    std::string nick = obj[0];
    if (!Parsing::IsValidNick(nick))
    {
        user->ReplyMsg(ERR_ERRONEUSNICKNAME(user->getNickname(), nick));
        return;
    }
    User *new_user = _Server->getUser(nick);
    if (new_user && new_user != user)
    {
        user->ReplyMsg(ERR_NICKNAMEINUSE(user->getNickname(), nick));
        return;
    }
    user->setNickname(nick);
    if (!user->IsRegistered())
        user->Registration();
}