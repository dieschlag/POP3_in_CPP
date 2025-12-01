#ifndef REQDELE
#define REQDELE

#include <string>
#include "Request.h"

class Server;

class RequestDele : public Request
{
private:
    std::string index_to_delete;    
public:
    RequestDele(std::string command_arg): index_to_delete(command_arg){};
    std::string get_arg() const {return index_to_delete;};
    virtual Response* accept(Server& s) const override;
};

#endif