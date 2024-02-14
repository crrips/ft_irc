// #include "Commands.hpp"

// void Commands::Mode(User *user, std::vector<std::string> obj)
// {
//     if (obj.size() < 2)
//     {
//         user->SendMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
//         return;
//     }

//     std::string channelName = obj[0];
//     std::string mode = obj[1];

//     Channel *channel = _Server->getChannel(channelName);
//     if (channel == NULL)
//     {
//         user->SendMsg(ERR_NOSUCHCHANNEL(user->getNickname(), channelName));
//         return;
//     }

// }