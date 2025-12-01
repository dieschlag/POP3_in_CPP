#ifndef REQRETR
#define REQRETR

#include <string>
#include "Request.h"

class Server;

class RequestRetr : public Request
{
private:
    std::string index_to_retreive;    
public:
    RequestRetr(std::string command_arg): index_to_retreive(command_arg){};
    std::string get_arg() const {return index_to_retreive;};
    virtual Response* accept(Server& s) const override;
};





#endif