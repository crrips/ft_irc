#include "Commands.hpp"

void Commands::Quit(User *user, std::vector<std::string> obj)
{
    if (obj.empty())
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "QUIT"));
        return ;
    }
    std::string reason = obj[0];
    if (reason[0] == ':')
        reason = reason.substr(1);
    user->setQuit(true);
    user->ReplyMsg(RPL_QUIT(user->getNickname(), reason));
}
