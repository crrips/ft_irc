#include "Channel.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "./Commands/Commands.hpp"

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {   
        try
        {
            Parsing::IsValidNumeric(argv[i]);
        }
        catch(const std::exception& e)
        {
            std::cout<<e.what()<<std::endl;
            return 1;
        }
    }
    if(argc != 3)
        std::cout<<"\33[1;31mErrror: Argument error!\33[1;0m"<<std::endl;

    User *user = new User(1, "testHost", "testNick", "testUser");
    Channel *channel = new Channel("#testChannel", "testPass", user);
    Commands *cmd = new Commands();
    cmd->_Server = new Server(atoi(argv[1]), argv[2]);

    channel->join(user);
    channel->kick(user, "testKick");

    // std::vector<std::string> obj;
    // obj.push_back("test1");
    // obj.push_back("test2");
    // cmd->Invite(user, obj);

    std::vector<std::string> obj_join;
    obj_join.push_back("#testChannel");
    obj_join.push_back("testPass");
    cmd->Join(user, obj_join);

    delete user;
    delete channel;

    return 0;
}