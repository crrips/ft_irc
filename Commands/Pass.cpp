#include "Commands.hpp"

void Commands::Pass(User *user, std::vector<std::string> obj)
{
    if(obj.size() != 1)
    {
        user->SendMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "PASS"));
        return;
    }

    else if(user->IsRegistered())
    {
        user->SendMsg(ERR_ALREADYREGISTERED(user->getNickname()));
        return;
    }

    else if (_Server->getPassword() != obj[0].substr(obj[0][0] == ':' ? 1 : 0))
    {
        user->ReplyMsg(ERR_PASSWDMISMATCH(user->getNickname()));
        return;
    }
    user->setPass();
    user->Registration();


}