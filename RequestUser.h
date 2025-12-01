#ifndef REQUSER
#define REQUSER

#include <string>
#include "Request.h"


class Server;

class RequestUser : public Request
{
private:
    std::string username;
public:
    RequestUser(std::string args) : username{args}{};
    std::string get_arg() const {return username;} ;
    virtual Response* accept(Server& s) const override;
};





#endif