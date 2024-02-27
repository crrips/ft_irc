#include "Commands.hpp"
#include <fstream>

void Commands::Transfer(User *user, std::vector<std::string> obj)
{
    if (obj.size() < 1)
    {
        user->ReplyMsg(ERR_NEEDMOREPARAMS(user->getNickname(), "TRANSFER"));
        return ;
    }

    std::string input = obj[0];

    for (size_t i = 1; i < obj.size(); i++)
        input += " " + obj[i];

    std::fstream file;
    file.open(input);
    if (!file.is_open())
        return ;
    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::ofstream transfer;
    transfer.open("transfer.txt");
    transfer << fileContent;
    transfer.close();
}