#include "Server.hpp"

// Server::Server()
// {

// }

// Server::~Server()
// {
    
// }

// Channel *Server::getChannel(std::string const &name)
// {
//     try
//     {
//         return _Channel.at(name);
//     }
//     catch(const std::exception& e)
//     {
//         return NULL;
//     }
// }

int Server::getPort()
{
    return (_Port);
}